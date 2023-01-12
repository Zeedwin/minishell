#include "shell.h"

int quotecheker(char *s, char c)
{
    int i;
    int simpq;

    i = 0;
    simpq = 0;

    while(s[i])
    {
     if(s[i] == '"')
         simpq++;
     i++;
    }
    if(count % 2 == 0)
     return (1);
    else
         return (0);
}