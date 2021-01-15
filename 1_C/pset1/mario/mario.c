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
        // print left pyramid
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

        // print margin
        for (int j = n; j == n || j == n + 1; j++)
        {
            printf(" ");
        }

        // print right pyramid
        for (int j = n; j < n + 1 + i; j++)
        {
            printf("#");
        }

        printf("\n");
    }
}