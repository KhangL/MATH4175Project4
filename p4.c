#include <stdio.h>

#define M 6

static const unsigned char S_box[2][8]  = {{0x6, 0x5, 0x1, 0x0, 0x3, 0x2, 0x7, 0x4}, // I -> O
                                           {0x3, 0x2, 0x5, 0x4, 0x7, 0x1, 0x0, 0x6}}; // O -> I
static const unsigned char ciphertext[] = {0x13, 0x2E, 0x25};
static const unsigned char y_star[]     = {0x1B, 0x3E, 0x05};
static const unsigned char trails[]     = {0x20, 0x30, 0x38};
static const float propRatios[] = {(float)1/4, (float)1/8, (float)1/8};

int main()
{
    unsigned char counter[] = {0, 0, 0};
    float C = 0;
    for (unsigned char i = 0x00; i < 0x03; i++)
    {
        printf("Trail: %d\n", i);
        // Iterate through every key (0b000 - 0b111)
        for (unsigned char k = 0x00; k < 0x08; k++)
        {
            printf("\tK = %d, ", k);
            unsigned char J = (k ^ (ciphertext[i]>>3)); // K ^ C = J 
            printf("J = 0x%01X, ", J);
            unsigned char H = S_box[1][J]; // Unshuffle J = H
            printf("H = 0x%01X, ", H);
            unsigned char J_star = (k ^ (y_star[i]>>3)); // K ^ y* = J*
            printf("J* = 0x%01X, ", J_star);
            unsigned char H_star = S_box[1][J_star]; // Unshuffle J* = H*
            printf("H* = 0x%01X, ", H_star);
            unsigned char H_prime = H ^ H_star; // H + H* = H' 
            printf("H' = 0x%01X\n", H_prime);
            if (H_prime == (trails[i]>>3)) counter[i]++;
        }
        printf("Counter %u: %u\n", i+1, counter[i]);
        C += propRatios[i] * counter[i];
    }

    printf("C = %.04f", C);
    return 0;
}