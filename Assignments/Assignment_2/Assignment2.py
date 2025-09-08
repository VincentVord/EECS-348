#EECS 348 Assignment 2
#
#Inputs: 
#Output: 
#Collaborators: None
#EECS 268 material, StackOverflow, ChatGPT
#Vincent Vordtriede
#9/7/2025

def count_empty_cells(M):
    e = 0
    for row in M:
        for cell in row:
            if cell == "_":
                e +=1 #get count of empty cells
    return e

def is_safe(M, row, col, num): #check to see if a number is safe to be placed
    num = str(num) #make num a string so it fits with the input array
    for x in range(9):     # Check if num exists in the current row
        if M[row][x] == num: #if duplicate found
            return False 

    for x in range(9):    # Check if num exists in the current col
        if M[x][col] == num: #if duplicate found
            return False

    # Check if num exists in the 3x3 sub-matrix
    startRow = row - (row % 3)
    startCol = col - (col % 3)

    for i in range(3):
        for j in range(3):
            if M[i + startRow][j + startCol] == num:
                return False

    return True

def rec_solve(M,row,col,k):
    if k == 81: #if all cells filled
        return True #solution found
    
    if col == 9: #if at the last column of the row, go down to the next row
        row += 1
        col = 0

    if M[row][col] !='_': #if the cell is filled, go to the next cell (k does not change)
        return rec_solve(M, row, col + 1, k) #recurse with next cell
    else:
        for num in range(1,10): #test all numbers 1 through 9
            if is_safe(M, row, col, num): #if the inputted number is safe
                M[row][col] = str(num) #write that number to the empty cell
                k += 1 #increment k 
                if rec_solve(M,row,col+1,k): #check if a solution has been found
                    return True #solution found
                else: #if not,
                    M[row][col] = '_' #rewrite to empty and backtrack
                    k -=1 #decrement k
        return False #if no safe numbers are found in any connfiguration, no solution exists


def solve(M):
    e = count_empty_cells(M) #get starting number of empty cells
    k = 81 - e #get starting number of full cells
    return rec_solve(M,0,0,k)
    
    
def main():
    inputmatrix = [] #declare empty list
    user_file = input("Enter the name of the sudoku puzzle file you want to solve: ") #prompt user for the file name
    with open(user_file, 'r') as file: #open the input file
        for line in file: #for each line in the file
            cleaned_line = line.replace("\n", "") #remove the newlines
            row = cleaned_line.split(" ") #split each element by spaces into a new list
            inputmatrix.append(row) #add each row list to the inputmatrix list (forming a list of lists)

    print(f"{user_file}:")
    if solve(inputmatrix): #if solution is found
        for row in inputmatrix: #print the 
            print(" ".join(map(str, row))) #got this code from geeksforgeeks to print out the matrix cleanly
    else:
        print("No solution exists") #if the function returns False, no solution exists

main() #call main