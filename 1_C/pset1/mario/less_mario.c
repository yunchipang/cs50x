#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // prompt user for an int between 1 and 8 inclusive
    int n;
    do
    {
        n = get_int("height: ");
    }
    while (n < 1 || n > 8);

    // print the pyramid
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i + j < n - 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}