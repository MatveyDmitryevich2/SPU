#include <stdio.h>

int factorial(int number)
{
    if (number > 0)
    {
        return number * factorial(number - 1);
    }
    return 1;
}

int main()
{
    int a = factorial(3);
    // int a = 1;
    // for ( int i = 5; i > 0; i--)
    // {
    //     a = a * i;
    // }

    printf("%d\n", a);

    return 0;
}
