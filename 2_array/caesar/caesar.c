#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[])
{
    // check if the command-line argument is a non-negative integer
    if (argc == 2)
    {
        int non_digit = 0;
        for (int i = 0, n = strlen(argv[1]); i < n; i++)
        {
            if (isdigit(argv[1][i]))
            {
                continue;
            }
            else
            {
                non_digit++;
            }
        }

        if (non_digit != 0)
        {
            printf("Usage: ./caesar key\n");
        }
    }
    else
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }

    // convert string argv[1] to an integer
    int key = atoi(argv[1]);
    // printf("key: %i\n", key);

    // get plaintext
    string plaintext = get_string("plaintext: ");

    // encipher the plaintext
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++)
    {
        if (isalpha(plaintext[i]))
        {
            // 1. convert ascii to alphabetical index
            // 2. shift by key
            // 3. convert back to ascii
            if (isupper(plaintext[i]))
            {
                plaintext[i] -= 65;
                plaintext[i] = (plaintext[i] + key) % 26;
                plaintext[i] += 65;
            }
            else // islower(plaintext[i])
            {
                plaintext[i] -= 97;
                plaintext[i] = (plaintext[i] + key) % 26;
                plaintext[i] += 97;
            }
            // printf("%i, %c\n", plaintext[i], plaintext[i]);
        }
        else
        {
            continue;
        }
    }

    // print the ciphertext
    printf("ciphertext: %s\n", plaintext);
}