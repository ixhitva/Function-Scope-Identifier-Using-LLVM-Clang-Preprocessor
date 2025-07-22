#include <stdio.h>

// Function to multiply two integers
int multiply(int a, int b) {
    return a * b;
}

int main() {
    int num1, num2, result;

    // Input from user
    printf("Enter two numbers: ");
    scanf("%d %d", &num1, &num2);

    // Calling the multiply function
    result = multiply(num1, num2);

    // Displaying the result
    printf("The product of %d and %d is %d\n", num1, num2, result);

    return 0;
}

