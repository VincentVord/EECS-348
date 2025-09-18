#include "isOdd.h"
#include "isEven.h"


#include <stdio.h>

int main() {
    int num;
    printf("Enter an integer: ");
    scanf("%d", &num);
    isOdd(num);
    return 0;
}
