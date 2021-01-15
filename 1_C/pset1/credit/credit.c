#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    // prompt user for credit card number input
    long n;
    do
    {
        n = get_long("Number: ");
    }
    while (n < 0);

    // checksum
    // 1. convert n to string and define d as the number of digits of n
    char str[32];
    sprintf(str, "%li", n);
    int length = strlen(str);
    // printf("length: %i\n", length);

    // 2. sum up digits by group
    int sum = 0;
    int j;
    // 2.1 every other number from the second last digit
    for (int i = length - 2; i >= 0; i -= 2)
    {
        j = str[i] - '0';
        int two_n = 2 * j;
        sum += ((two_n / 10) + (two_n % 10));
    }
    // 2.2 digits that are not included above
    for (int i = length - 1; i >= 0; i -= 2)
    {
        j = str[i] - '0';
        sum += j;
    }

    // verification
    // printf("sum: %i\n", sum);
    // printf("length: %i\n", length);

    // if the number pass the checksum
    if (sum % 10 == 0)
    {
        if (length == 15 && str[0] == '3' && (str[1] == '4' || str[1] == '7'))
        {
            printf("AMEX\n");
        }

        else if (length == 16 && str[0] == '5' && (str[1] == '1' || str[1] == '2' || str[1] == '3' || str[1] == '4' || str[1] == '5'))
        {
            printf("MASTERCARD\n");
        }

        else if ((length == 13 || length == 16) && str[0] == '4')
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }
    else
    {
        printf("INVALID\n");
    }
}