#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // prompt user for input
    float dollars;
    int cents;
    do
    {
        dollars = get_float("change owed: ");
        // convert dollars to cents
        cents = round(dollars * 100);
    }
    while (dollars < 0);
    //printf("%i\n", cents);

    // define the coins available
    int money[4];
    money[0] = 25;
    money[1] = 10;
    money[2] = 5;
    money[3] = 1;

    //counting coins
    int coins = 0;
    for (int i = 0; i < 4; i++)
    {
        while (cents >= money[i])
        {
            cents -= money[i];
            coins++;
        }
    }
    printf("%i\n", coins);
}