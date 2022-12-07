#include <stdio.h>

#define M 6

static const unsigned char S_box[2][8]  = {{0x6, 0x5, 0x1, 0x0, 0x3, 0x2, 0x7, 0x4}, // I -> O
                                           {0x3, 0x2, 0x5, 0x4, 0x7, 0x1, 0x0, 0x6}}; // O -> I
static const unsigned char ciphertext[] = {0x32, 0x1D, 0x29};
static const unsigned char y_star[]     = {0x36, 0x1F, 0x28};
static const unsigned char trails[]     = {0x1, 0x3, 0x7};
static const float propRatios[] = {(float)1/4, (float)1/8, (float)1/8};

int main()
{
    unsigned char counter[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Counter for each key
    float C[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Weighted average count 

    // Iterate over the three trails
    for (unsigned char i = 0x00; i < 0x03; i++)
    {
        printf("Trail: %u\n", i+1);

        // Iterate through each 4-tuple
        for (unsigned char j = 0; j < 0x03; j++) {
            printf("\n\tY = 0x%02X, Y* = 0x%02X\n", ciphertext[j], y_star[j]);

            // Iterate through every key (0b000 - 0b111)
            for (unsigned char k = 0x00; k < 0x08; k++)
            {
                printf("\t\tK = %d, ", k);
                unsigned char J = (k ^ (ciphertext[j] & 0x07)); // K ^ C = J 
                printf("J = 0x%01X, ", J);
                unsigned char H = S_box[1][J]; // Unshuffle J = H
                printf("H = 0x%01X, ", H);
                unsigned char J_star = (k ^ (y_star[j] & 0x07)); // K ^ y* = J*
                printf("J* = 0x%01X, ", J_star);
                unsigned char H_star = S_box[1][J_star]; // Unshuffle J* = H*
                printf("H* = 0x%01X, ", H_star);
                unsigned char H_prime = H ^ H_star; // H + H* = H' 
                printf("H' = 0x%01X\n", H_prime);
                if (H_prime == (trails[i])) counter[k]++;
            }
        }

        // Prints Counter table
        printf("\nCounter: %u\t", i+1);
        for (unsigned char j = 0; j < 0x08; j++) {
            printf("0x%1X ", j);
        }
        printf("\n         \t");
        for (unsigned char j = 0; j < 0x08; j++) {
            printf("%2u  ", counter[j]);
            C[j] += propRatios[i]*counter[j];
        }
        printf("\n\n");
    }

    // Prints Counter table
    printf("\nC   ");
    for (unsigned char j = 0; j < 0x08; j++) {
        printf("0x%1X       ", j);
    }
    printf("\n   ");
    for (unsigned char j = 0; j < 0x08; j++) {
        printf("%.04f    ", C[j]);
    }
    printf("\n\n");
    return 0;
}