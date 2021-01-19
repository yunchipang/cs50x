#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

int main(void)
{
    // prompt the user for text input
    string text = get_string("Text: ");

    // count number of letters, words and sentences
    int letters = 0;
    int words = 0;
    int sentences = 0;
    int spaces = 0;
    int puncts = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isalpha(text[i]))
        {
            letters++;
        }
        else if (isspace(text[i]))
        {
            spaces++;
        }
        else if ((text[i] == '.') || (text[i] == '!') || (text[i] == '?'))
        {
            puncts++;
        }
        else
        {
            continue;
        }
    }
    words = spaces + 1;
    sentences = puncts;

    /*
    printf("%i letter(s)\n", letters);
    printf("%i word(s)\n", words);
    printf("%i sentence(s)\n", sentences);
    */

    // calculate index
    float L = ((float) letters * 100) / (float) words;
    float S = ((float) sentences * 100) / (float) words;
    float index = 0.0588 * L - 0.296 * S - 15.8;

    /*
    printf("%f\n", L);
    printf("%f\n", S);
    printf("%f\n", index);
    */

    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %.0f\n", round(index));
    }
}