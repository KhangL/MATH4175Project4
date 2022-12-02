#include <stdio.h>
#include <stdbool.h>

#define M 6

static const unsigned char S_box[2][8] = {{0x6, 0x5, 0x1, 0x0, 0x3, 0x2, 0x7, 0x4}, // I -> O
                                          {0x3, 0x2, 0x5, 0x4, 0x7, 0x1, 0x0, 0x6}}; // O -> I
static const unsigned char plaintext[] = {0x27, 0x07, 0x0C, 0x18, 0x08, 0x1A};
static const unsigned char ciphertext[] = {0x24, 0x32, 0x39, 0x1D, 0x0D, 0x29};

int main()
{
    unsigned char counter[] = {0, 0, 0, 0, 0, 0, 0, 0};
    for (unsigned char i = 0x00; i < 0x06; i++)
    {
        printf("Round: %d, ", i);

        // Grab Plaintext values
        bool p1 = (plaintext[i] & 0x20) >> (M - 1); // Bitmask 0x20 (0010 0000)
        bool p2 = (plaintext[i] & 0x10) >> (M - 2); // Bitmask 0x10 (0001 0000)
        bool p4 = (plaintext[i] & 0x04) >> (M - 4); // Bitmask 0x04 (0000 0100)
        bool p5 = (plaintext[i] & 0x02) >> (M - 5); // Bitmask 0x02 (0000 0010)

        bool pSum = p1 ^ p2 ^ p4 ^ p5;
        printf("pSum: %d\n", pSum); // Compute P1 ^ P2 ^ P4 ^ P5 ^ H1
 

        // Iterate through every key
        for (unsigned char k = 0x00; k < 0x08; k++)
        {
            printf("\tK: %d, ", k);
            unsigned char J = (ciphertext[i] ^ (k << 3)) >> 3 & 0x07; // C ^ K = J
            printf("J: 0x%01X, ", J);
            unsigned char H = S_box[1][J]; // Unshuffle J = H
            printf("H: %d, ", H);
            printf("H1: %d, ", (H >> 2));
            if (!(pSum ^ (H >> 2))) counter[k]++; // add pSum XOR H1 to the counter for K
            printf("Sum %d: %d\n", k, pSum ^ (H >> 2));
        }
        printf("\n");
    }

    // Print counter values
    for (unsigned char i = 0; i < 0x08; i++)
    {
        printf("Counter %u: %u\n", i, counter[i]);
    }
    return 0;
}