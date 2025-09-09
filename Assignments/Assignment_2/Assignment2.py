#EECS 348 Assignment 2
#Recursive depth-first search sudoku solver program
#Inputs: Input puzzle file name
#Output:Puzzle file name, number of possible solutions, and all possible solutions
#Collaborators: None
#StackOverflow, ChatGPT, geeksforgeeks.org
#Vincent Vordtriede
#9/8/2025

import copy #import copy for the recursive solving function (used ChatGPT to figure this out)

class Sudoku: #defines the Sudoku Class
    def __init__(self, board): #initializes the matrix as board
        self.board = board #sets the input to self.board
        self.solutions = [] #initializes an empty solutions list 

    def count_empty_cells(self): #function that counts all of the empty cells in the matrix
        e = 0 #initialize e as 0
        for row in self.board: #for each row in the matrix
            for cell in row: #for each cell in each row
                if cell == "_": #if the cell is an underscore
                    e +=1 #increment e by 1
        return e #return the total number of empty cells

    def is_safe(self, row, col, num): #check to see if a number is safe to be placed
        num = str(num) #make num a string so it fits with the input array

        for x in range(9):# Check if num exists in the current row
            if self.board[row][x] == num: #if duplicate found
                return False  #this cell is not safe

        for x in range(9):    # Check if num exists in the current col
            if self.board[x][col] == num: #if duplicate found
                return False #this cell is not safe

        # Check if num exists in the 3x3 sub-matrix
        startRow = row - (row % 3) #find the beginning row number of the current sub-matrix
        startCol = col - (col % 3) #find the beginning row number of the current sub-matrix

        for i in range(3): #iterate through each row
            for j in range(3): #of each column
                if self.board[i + startRow][j + startCol] == num: #and check if num exists in the current row/col
                    return False #if it does return False

        return True #otherwise return True, the cell is safe

    def rec_solve(self,row,col,k): #recursive solver function -- modified a different function from geeksforgeeks.org to fit this solver
        if k == 81: #if all cells filled
            self.solutions.append(copy.deepcopy(self.board)) #solution found, copy the solution to the solutions list (ensuring it is a completely independant copy) --used ChatGPT to figure this one out
            return #stop here once a solution is found
            
        if col == 9: #if at the last column of the row, go down to the next row
            row += 1 #increment row by 1
            col = 0 #start back at the left side of the matrix

        if self.board[row][col] !='_': #if the cell is filled, go to the next cell (k does not change)
            return self.rec_solve(row, col + 1, k) #recurse with next cell
        else:
            for num in range(1,10): #test all numbers 1 through 9
                if self.is_safe(row, col, num): #if the inputted number is safe
                    self.board[row][col] = str(num) #write that number to the empty cell
                    k += 1 #increment k (total filled cells + 1)
                    self.rec_solve(row,col+1,k) #recurse to next cell
                    self.board[row][col] = '_' #if rec_solve doesn't return, then a solution was not found yet, so backtrack and retwrute the current cell to an underscore
                    k -=1 #decrement k (total filled cells - 1)


    def solve(self): #helper function
        e = self.count_empty_cells() #get starting number of empty cells
        k = 81 - e #get starting number of full cells
        self.rec_solve(0,0,k) #call recursive solver function
        return self.solutions #return the solutions list
    
    
def main(): #defines the main function
    inputmatrix = [] #declare empty list
    user_file = input("Enter the name of the sudoku puzzle file you want to solve: ") #prompt user for the file name
    with open(user_file, 'r') as file: #open the input file
        for line in file: #for each line in the file
            cleaned_line = line.replace("\n", "") #remove the newlines
            row = cleaned_line.split(" ") #split each element by spaces into a new list
            inputmatrix.append(row) #add each row list to the inputmatrix list (forming a list of lists)
    
    sudoku = Sudoku(inputmatrix)#create instance of the Sudoku Class

    print("=================") #formatting
    print(f"{user_file}:\n") #print out puzzle file
    solutions = sudoku.solve() #call the solve function on the input matrix

    if solutions: #if solutions were found...
        print(f"{len(solutions)} solutions found\n") #use the length of the solutions list to find the number of solutions
        for matrix in solutions: #for every matrix in solutions
            for row in matrix: #for every row in each matrix
                print(" ".join(row))#print each row list as a string delimited by spaces
            print('\n') #add a newline between rows 
    else: #otherwise...
        print("No solution exists") #print no solution exists

main() #call main