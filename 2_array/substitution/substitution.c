#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// pre-declare functions
bool all_alpha(string str);
bool no_repeats(string str);


int main(int argc, string argv[])
{
    // get substitution key + validate it
    if (argc == 2)
    {
        if (all_alpha(argv[1]) == false)
        {
            printf("Key must contain only alphabetic characters.\n");
            return 1;
        }
        else if (no_repeats(argv[1]) == false)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
        else if (strlen(argv[1]) != 26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    // prompt user for plaintext
    string plaintext = get_string("plaintext: ");

    // encipher the plaintext
    int len = strlen(plaintext);

    // mapping -> create an array of ascii difference called "diff"
    // convert key to all uppercase in advance
    int diff[26] = {};
    int base = 65;
    for (int i = 0; i < 26; i++)
    {
        diff[i] = toupper(argv[1][i]) - base;
        base++;
        //printf("%i, ", diff[i]);
    }
    //printf("\n");

    for (int i = 0; i < len; i++)
    {
        if (isupper(plaintext[i]))
        {
            // convert plaintext[i] to it's alphabetical index
            int alpha_index = plaintext[i] - 65;
            // add diff[alpha_index], return c as deciphered char
            plaintext[i] = (alpha_index + diff[alpha_index]) + 65;
        }
        else if (islower(plaintext[i]))
        {
            int alpha_index = plaintext[i] - 97;
            plaintext[i] = (alpha_index + diff[alpha_index]) + 97;
        }
    }

    // print out ciphertext
    printf("ciphertext: %s\n", plaintext);
}


// declare functions
bool all_alpha(string str)
{
    for (int i = 0, n = strlen(str); i < n; i++)
    {
        if (!isalpha(str[i]))
        {
            return false;
        }
    }
    return true;
}

bool no_repeats(string str)
{
    int n = strlen(str);
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (str[i] == str[j])
            {
                return false;
            }
        }
    }
    return true;
}