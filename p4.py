#MATH4175 Project 3

# MAIN FUNCTION
def main():
    # (SBOX FUNCTION HERE) Based on S-box, make normalized linear approximation table
    # sbox array? The input they give will match the hexadecimal and can be used for index?


    sboxBitsInput = [[0,0,0],[0,0,1],[0,1,0],[0,1,1],[1,0,0],[1,0,1],[1,1,0],[1,1,1]]
    sboxBitsOutput = [[1,1,0],[1,1,0],[1,1,0],[1,1,0],[1,1,0],[1,1,0],[1,1,0],[1,1,0]]

    counterTable = [ [0]*8 for i in range(8)]
    for x in range(0,8):
        for y in range(0,8):
            counter = 0
            currentCheckArrayX =[x/4,x%4/2,x%2]
            currentCheckArrayY =[x/4,x%4/2,x%2]
            for x1 in range(0,8):
                currentBitInputArray = sboxBitsInput[x1]
                currentBitOutputArray = sboxBitsOutput[x1]
                for x in range(0,4):
                    # This is where I add them
                # After that, I can add the two results and check if equal 0, if so, then add counter.
            counterTable[x][y] = counter

#     (Might Need Not Sure)
#     args = sys.argv[1:]
#     original_string = open(args[0],"r").read()


# SBOX FUNCTION
#  Could hardcode the ruleset here and then run through the table?
#  (BIT-TO-HEXA HELPER NEEDED HERE BEFORE RETURN)

# Bias Function return (Table[a][b]-4)/8




# ASSIGNMENT TRANSFERED OVER.
# ________________________________________________________________
# S-BOX DEFINITION
# input 000 001 010 011 100 101 110 111
# ouput 110 101 001 000 011 010 111 100

# In terms of hexadecimal
# input 0 1 2 3 4 5 6 7
# ouput 6 5 1 0 3 2 7 4

# 1: Create the normalized linear approximation table for the
# given S-box similar to the table given in the slide 18 of
# sec4.3 class notes

# REMARK: Your input sum and output sum should be from 0 to 7
# in hexadecimal notation. So your table should be
# an 8 ×8 table and the formula for the entries are NL(a,b) −4.

# 2: Find a linear approximation trail with nonzero bias, 
# analogous to slides 22 of section 4.3 in class notes, which
# connects the plaintext bits P1, P2, P4, and P5 to the bit H1.
#  You should sketch the trail and attach as a pdf file.

# 3: What is the total bias of the linear approximation trail you found?

# 4. Suppose you are given the following known plaintext and ciphertext 
# pairs for this cipher, all encrypted with the same (unknown) key:

# Plaintext Ciphertext
# 100111 100100
# 000111 110010
# 001100 111001
# 011000 011101
# 001000 001101
# 011010 101001

# 5. Determine the first and the third bits of the subkey K4.
# Remark: This problem has been specifically constructed so that a very
# small number of plaintexts and ciphertexts is sufficient to determine
# two subkey bits.

# 6. Why is this information insufficient to determine the second bit of 
# the subkey K4?.