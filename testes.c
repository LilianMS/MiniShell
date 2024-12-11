
#include <stdio.h>
#include <string.h>


void ft_rem_chr(char *str, char c)
{
    char *newline;

    newline = strchr(str, c);
    if (newline)
        *newline = '\0';
}

