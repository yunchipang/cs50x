#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // prompt the user for their name
    string name = get_string("What is your name?\n");

    // print out hello
    printf("hello, %s\n", name);
}