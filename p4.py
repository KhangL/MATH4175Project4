#MATH4175 Project 4

# MAIN FUNCTION
def main():
    # This is the stated sbox given
    sboxBitsInput = [[0,0,0],[0,0,1],[0,1,0],[0,1,1],[1,0,0],[1,0,1],[1,1,0],[1,1,1]]
    sboxBitsOutput = [[1,1,0],[1,0,1],[0,0,1],[0,0,0],[0,1,1],[0,1,0],[1,1,1],[1,0,0]]

    # Table that will store the counters
    counterTable = [ [0]*8 for i in range(8)]
    for x in range(0,8): 
        inputDifference =[x//4, (x%4)//2, x%2]
        for bits in range(0,8):
            currentBitInputArray = sboxBitsInput[bits]
            currentBitOutputArray = sboxBitsOutput[bits]
            xDifference = [(currentBitInputArray[0] + inputDifference[0]) %2, (currentBitInputArray[1] + inputDifference[1]) %2, (currentBitInputArray[2] + inputDifference[2]) %2]
            # Go through array trying sboxBitsInput, trying to find index to find correlating yDifference
            yDifference = sboxBitsOutput[sboxBitsInput.index(xDifference)]
            yFinalDifference = [(currentBitOutputArray[0] + yDifference[0]) %2, (currentBitOutputArray[1] + yDifference[1]) %2, (currentBitOutputArray[2] + yDifference[2]) %2]
            # Convert Final Difference to a number to add to the counter table for that row.
            indexNum = yFinalDifference[0] * 4 + yFinalDifference[1] * 2 + yFinalDifference[2] * 1
            counterTable[x][indexNum] = counterTable[x][indexNum] + 1

    # Formatting for the print
    print(" | ", end="")
    print(" ", end="")

    for x in range(8):
        print(" |  ", end="")
        print(x, end="")
    print(" | ")

    for x in range(8):
        print(" | ", end="")
        print(x, end="")
        for y in range(8):
            print(" | ", end="")
            if (counterTable[x][y] > 0):
                print("+", end="")
                print(counterTable[x][y], end="")
            elif (counterTable[x][y] == 0):
                print(" ", end="")
                print(counterTable[x][y], end="")
            else:
                print(counterTable[x][y], end="")
        print(" | ")

main()