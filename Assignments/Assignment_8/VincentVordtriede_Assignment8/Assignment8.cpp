// EECS 348 Assignment 8
// Purpose: A debugged C++ program with corrected logical errors.
// Inputs: None
// Output: An average of 3 numbers, the sum of even numbers <=6, and a statement printing if a given number is positive or not.
// Collaborators: None
// Sources: None
// Vincent Vordtriede
// 12/2/2025

#include <iostream> // import iostream library 

int main() { // main function
    int num1 = 10; //define first num
    int num2 = 20; //define second num
    int num3 = 30; //define third num
    //D double average = (num1 + num2 + num3) / 3;
    double average = (num1 + num2 + num3) / 3.0; //A this line of code now will perform floating point division isntead of integer division only, as well as prevents integer overflow by converting the sum to a double
    std::cout << "Average: " << average << std::endl; //print the average

    int sum_even = 0; //create sum_even varaible
    //D for (int i = 0; i <= 5; i++) {
        for (int i = 0; i <= 6; i++) { //A this line of code will now correctly count up to 6 (inclusive) instead of 5
        if (i % 2 == 0) { //if the given number is even
            sum_even += i; //add it to the even sum
        }
    }
    std::cout << "Sum of positive even numbers <= 6: " << sum_even << std::endl; // print the sum of even numbers

    int value = 0; //initialize the value to 0
    //D if (value > 0 || value == 0) {
    if (value > 0) { //A this line of code will now cause the if statement to print that the value is positive only if it is greater than zero, not equal to zero.
        std::cout << value << " is positive." << std::endl; // print if the value is positive
    } else { //otherwise
        std::cout << value << " is not positive." << std::endl; //print if the value os not positive
    }

    return 0; //end main function
}
