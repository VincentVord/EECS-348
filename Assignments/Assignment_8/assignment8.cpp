#include <iostream>
int main() {
    int num1 = 10;
    int num2 = 20;
    int num3 = 30;
    //D double average = (num1 + num2 + num3) / 3;
    double average = (num1 + num2 + num3) / 3.0; //A this line of code now will perform floating point division isntead of integer division only, as well as prevents integer overflow by converting the sum to a double
    std::cout << "Average: " << average << std::endl; 

    int sum_even = 0;
    //D for (int i = 0; i <= 5; i++) {
        for (int i = 0; i <= 6; i++) { //A this line of code will now correctly count up to 6 (inclusive) instead of 5
        if (i % 2 == 0) {
            sum_even += i;
        }
    }
    std::cout << "Sum of positive even numbers <= 6: " << sum_even << std::endl;

    int value = -5;
    if (value > 0 || value == 0) {
        std::cout << value << " is positive." << std::endl;
    } else {
        std::cout << value << " is not positive." << std::endl;
    }

    return 0;
}
