#EECS 348 Assignment 3
#Interactive Nim game in python
#Inputs: Each players row number and number of stars
#Output: Player tracker, invalid move errors, the Nim board itself
#Collaborators: None
#Sources: None
#Vincent Vordtriede
#9/22/2025


class Nim: #create the Nim class
    def __init__(self, board): #initialize the starting board
        self.board = board #define the input board as self.board
    
    def is_valid(self, row, stars): #this functions checks to see if a given move is valid
        current_row = self.board[row-1] #get the current row (as row 1 is actually row 0)
        if len(current_row) >= stars: #if the length of the current row greater or equal to the number of stars to be removed...
            return True #the move is valid
        else: #otherwise...
            return False #the move is invalid
        
    def is_game_over(self): #this function checks if the game has ended
        empty_rows = 0 #initialize the number of empty rows to 0
        for row in self.board: #loop through each row in the board
            if len(row) == 0: #if the row is empty
                empty_rows +=1 #add 1 to empty_rows
        if empty_rows == 5: #if all rows are empty
            return True #the game is over
        else: #otherwise
            return False #the game is not over
        
    def update_board(self, row, stars): #this function updates self.board after each move
        if self.is_valid(row, stars): #if the move is valid
            current_row = self.board[row-1] #get the current row (as row 1 is actually row 0)
            for i in range(0,stars): #loop through the current row the correct number of times
                current_row.pop() #remove the correct number of stars from the row
            return True #return True for error checking in main
        else: #otherwise
            return False #return False for error checking in main

    def print_board(self): #this function prints the board
        row_num = 1 #start at the first row
        for row in self.board: #loop through every row
            print(f"{row_num}: {' '.join(row)}") #print the row number and the contents of each row
            row_num +=1 #increment the row number
        print() #add a newline for cleaner output

def main(): #defines the main function
    print("Nim in Python!\n") #this block of code prints out the starting board at the beginning of each game
    print("1: * * * * *")
    print("2: * * * *")
    print("3: * * *")
    print("4: * *")
    print("5: *")
    print()

    start_board = [['*','*','*','*','*'], #this block of code creates the actual array that represents the starting board that will later be manipulated
                   ['*','*','*','*'],
                   ['*','*','*'],
                   ['*','*'],
                   ['*']]
    my_board = Nim(start_board) #create instance of the Nim class using start_board

    while True: #will loop until the game ends
        while True: #will loop until player 1 makes a valid move
            print("Player 1:\n======================") #print player 1
            player1_row = int(input("Enter a row number: ")) #prompt user for the row
            player1_stars = int(input("Stars to remove: ")) #prompt user for the number of stars
            if my_board.update_board(player1_row, player1_stars): #if update_board returns True
                my_board.print_board() #print the board
                break #break the while loop and continue
            else: #otherwise...
                print("Please enter a valid move.") #print error message
                my_board.print_board() #print the board again
                pass #continue looping with player 1

        if my_board.is_game_over(): #check if the game is over
            print("Player 1 wins!") #display the winner
            break #end the game

        while True: #will loop until player 2 makes a valid move
            print("Player 2:\n======================") #print player 2
            player2_row = int(input("Enter a row number: ")) #prompt user for the row
            player2_stars = int(input("Stars to remove: ")) #prompt user for the number of stars
            if my_board.update_board(player2_row, player2_stars): #if update_board returns True
                my_board.print_board() #print the board
                break #break the while loop and continue
            else: #otherwise...
                print("Please enter a valid move.") #print error message
                my_board.print_board() #print the board again
                pass #continue looping with player 2

        if my_board.is_game_over(): #check if the game is over
            print("Player 2 wins!") #display the winner
            break #end the game
main() #call main