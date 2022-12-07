#include <stdio.h>
#include <stdbool.h>

#define M 6

static const unsigned char S_box[2][8]  = {{0x6, 0x5, 0x1, 0x0, 0x3, 0x2, 0x7, 0x4}, // I -> O
                                           {0x3, 0x2, 0x5, 0x4, 0x7, 0x1, 0x0, 0x6}}; // O -> I
// static const unsigned char plaintext[]  = {0x07, 0x18, 0x1A};
// static const unsigned char x_star[]     = {0x06, 0x19, 0x1B};
// static const unsigned char ciphertext[] = {0x32, 0x1D, 0x29};
// static const unsigned char y_star[]     = {0x36, 0x1F, 0x28};
static const unsigned char ciphertext[] = {0x24, 0x39, 0x0D};
static const unsigned char y_star[]     = {0x3E, 0x20, 0x03};
static const unsigned char trails[]     = {0x20, 0x30, 0x38};

int main()
{
    unsigned char counter[] = {0, 0, 0};
    for (unsigned char i = 0x00; i < 0x03; i++)
    {
        printf("Trail: %d\n", i);
        // Iterate through every key (0b000 - 0b111)
        for (unsigned char k = 0x00; k < 0x08; k++)
        {
            printf("\tK = %d, ", k);
            unsigned char J = ((k << 3) ^ ciphertext[i]) >> 3; // K ^ C = J 
            printf("J = 0x%01X, ", J);
            unsigned char H = S_box[1][J]; // Unshuffle J = H
            printf("H = 0x%01X, ", H);
            unsigned char J_star = ((k << 3) ^ y_star[i]) >> 3; // K ^ y* = J*
            printf("J* = 0x%01X, ", J_star);
            unsigned char H_star = S_box[1][J_star];
            printf("H* = 0x%01X, ", H_star);
            unsigned char H_prime = H ^ H_star;
            printf("H' = 0x%01X\n", H_prime);
            if (H_prime & trails[i]) counter[i]++;
        }
        printf("\n");
    }

    // Print counter values
    for (unsigned char i = 0; i < 0x03; i++)
    {
        printf("Counter %u: %u\n", i+1, counter[i]);
    }
    return 0;
}