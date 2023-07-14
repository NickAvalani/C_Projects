/*
* Nick Avalani
* CSC 352, Fall 2022, Benjamin Dicken
* pythagorean.c
* This program calculates the hypotenuse of a right
* triangle by taking the other two sides as input from
* the user.
*/


#include <stdio.h>
#include<stdlib.h>
#include <math.h>

int main()
{   int num1 = 0;
    int num2 = 0;
    printf("Enter side A length:\n");
    scanf("%d", &num1);
    printf("Enter side B length:\n");
    scanf("%d", &num2);
    double hyp = sqrt((num1 * num1) + (num2 * num2));
    printf("Length of side C: %.2f\n", hyp);

    return 0;
}
