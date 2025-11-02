// EECS 348 Assignment 6
// This is a recursive sudoku puzzle solver implemented using OOP in C++
// Inputs: an input file
// Output: The name of the input file, number of solutions found, and the solutions themselves
// Collaborators: None
// Sources: My Lab 9, My Assignment 2, W3Schools
// Vincent Vordtriede
// 11/2/2025

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Sudoku { //define Sudoku class
    public: // all following functions can be accessed outside the class
        vector<vector<int>> board; //init board (input puzzle matrix)
        vector<vector<vector<int>>> solutions; //init soltuions list

        int count_empty_cells() { //function that returns the number of empty cells in the puzzle
            int e = 0; //number of empty cells
            for (int i=0; i<9; i++) { //loop through every row
                for (int j=0; j<9; j++) { //and every column
                    if (board[i][j] == 0) { //if the cell is 0 (empty)
                        e++; //add 1 to the number of empty cells
                    }
                }
            }
            return e; //return number of empty cells
        }

        bool is_safe (int row, int col, int num) { //function that checks if a given position is safe to insert a number in the puzzle
            for (int x=0; x<9; x++) { //check if num exists in the current row
                if (board[row][x] == num) { //if a duplicate is found
                    return false; //return false
                }
            }
            for (int x=0; x<9; x++) { //check if num exists in the current row
                if (board[x][col] == num) { //if a duplicate is found
                    return false; //return false
                }
            }
            //check if num exists in the 3x3 submatrix
            int startRow = row - (row % 3); //find the beginning row number of the current sub-matrix
            int startCol = col - (col % 3); //find the beginning col number of the current sub-matrix

            for (int i=0; i<3; i++) { //iterate through each row
                for (int j=0; j<3; j++) { //of each col
                    if (board[i+startRow][j+startCol] == num) { //check if num exists 
                        return false; //if it does return false
                    }
                }
            }
            return true; //otherwise return true
        }

        void rec_solve(int row, int col, int k) { //recursive solving function
            if (k == 81) { //k= total filled cells, so if k = 81 then the puzzle is done
                solutions.push_back(board); //take the current board and add it to the solutions list
                return; //leave that instance of the recursive function, continue searching for others
            }
            if (col == 9) { //when we reach the end of the row
                row++; //go down to the next row
                col = 0; //and start at column 0 again
            }
            if (board[row][col] != 0) { //if the current cell is filled, go to next cell
                return rec_solve(row, col+1, k); //next cell meaning col+1
            } else { //if the current cell is empty (a zero)
                for (int num=1; num<10; num++) { //test all numbers 1 through 9
                    if (is_safe(row, col, num)) { //if the number is safe
                        board[row][col] = num; //write that number to the empty cell
                        k++; //add 1 to the total filled cells
                        rec_solve(row, col+1, k); //recurse to the next cell
                        board[row][col] = 0; //if rec_solve doesn't return, then a solution was not found yet, so backtrack and retwrute the current cell to a zero
                        k--; //remove 1 from total filled cells
                    }
                }
            }
        }

        vector<vector<vector<int>>> solve() { //function that calls the recursive solver
            int e = count_empty_cells(); //get the number of empty cells
            int k = 81 - e; //get starting number of full cells
            rec_solve(0,0,k); //solve the puzzle starting at 0,0
            return solutions; //return the list of solution matrices
        }
};

vector<vector<int>> read_matrix(ifstream &File) { //function that reads the matrix file
    vector<vector<int>> matrix(9, vector<int>(9)); //create empty 9x9 matrix

    string val; //initialize a value string
    for (int i = 0; i<9; i++){ //loop through each line of the file
        for (int j = 0; j<9; j++){ //loop through each char in the line
            File >> val; //read the value from the file
            if (val == "_") { //if it is an underscore 
                matrix[i][j] = 0; //replace underscores with zeros
            } else { //otherwise...
                matrix[i][j] = stoi(val); //if it is a number than convert to an int and store it
            }
        }
    }
    return matrix; //return the matrix from the file
}

void print_matrix(const vector<vector<int>> &matrix) { //function for cleanly printing the matrix (borrowed from one of the previous labs)
    for (const auto &row : matrix) { //loop through each row
        for (int val : row) { //loop through each col
            cout << val << " "; //print the cell separated by spaces
        }
        cout << endl; //print a newline after every row
    }
}

int main() { //defines the main function
    string filename; //initialize the filename string
    cout << "Enter a file name: " <<endl; //prompt user for the input file name
    cin >> filename; //get the filenane from the input stream

    ifstream File(filename); //read the input file name
    if (!File) { // always check that the file opened successfully
        cerr << "Error: could not open file.\n"; //if the file name is invalid print error message
        return 1; //leave main
    }

    vector<vector<int>> puzzle = read_matrix(File); //define the puzzle variable that holds the matrix from the input file via read_matrix

    Sudoku sudoku; //create instance of the Sudoku class
    sudoku.board = puzzle; //set the classes board member to puzzle

    cout << "=================" << endl; //formatting
    cout << filename << ":\n" << endl; //print puzzle file name

    vector<vector<vector<int>>> solutions = sudoku.solve(); //get solutions list from class

    if (!solutions.empty()) { //if there are solutions in the list
        cout << solutions.size() << " solutions found\n" << endl; //print how many solutions there are
        for (size_t i = 0; i<solutions.size(); i++) { //loop through the solutions list
            print_matrix(solutions[i]); //print the matrices
            cout << endl; //add a newline after every solved puzzle matrix
        }    
    } else { //otherwise...
        cout << "No solutions exists" << endl; //print that there are no solutions found
    }
    return 0; //leave main
}

