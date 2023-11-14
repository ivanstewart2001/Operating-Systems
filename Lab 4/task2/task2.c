#include <stdio.h>
#include <stdlib.h>

/* Function prototypes */
int add(int a, int b);
int subtract(int a, int b);
int multiply(int a, int b);
int divide(int a, int b);
int exitprog (int a, int b);

/* Function pointer type */
typedef int (*Operation)(int a, int b);

int main(void)
{
    /* Array of function pointers */
    Operation operations[] = {add, subtract, multiply, divide};

    int a, b;
    printf("Operand 'a' : ");
    scanf("%d", &a);
    printf("Operand 'b' : ");
    scanf("%d", &b);

    int result;
    char operation;
    printf("Specify the operation to perform (0: add | 1: subtract | 2: Multiply | 3: divide | 4: exit): ");
    scanf(" %c", &operation);

    /* Convert character to array index */
    int operationIndex = operation - '0';

    /* Check if the operation is valid */
    if (operationIndex >= 0 && operationIndex <= 3)
    {
        /* Use function pointer to execute the corresponding operation */
        result = operations[operationIndex](a, b);

        /* Print the result */
        printf("x = %d\n", result);
    }
    else if (operationIndex == 4)
    {
        printf("Exiting program.\n");
    }
    else
    {
        printf("Invalid operation.\n");
    }

    return 0;
}

/* Function definitions */
int add(int a, int b)
{
    printf("Adding 'a' and 'b'\n");
    return a + b;
}

int subtract(int a, int b)
{
    printf("Subtracting 'b' from 'a'\n");
    return a - b;
}

int multiply(int a, int b)
{
    printf("Multiplying 'a' and 'b'\n");
    return a * b;
}

int divide(int a, int b)
{
    if (b != 0)
    {
        printf("Dividing 'a' by 'b'\n");
        return a / b;
    }
    else
    {
        printf("Error: Division by zero.\n");
        exit(EXIT_FAILURE);
    }
}

int exitprog(int a, int b){ 
	exit(1); 
}
