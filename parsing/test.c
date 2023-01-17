#include "shell.h"

int quotecheker(char *s, char c)
{
    int i;
    int simpq;
	int doubq;

    i = 0;
    simpq = 0;
	doubq = 0;

    while(s[i])
    {
    	if(s[i] == '"')
			doubq++;
		if(s[i] == 39)
        	simpq++;
     i++;
    }
    if((simpq % 2 == 0) || doubq % 2 == 0)
     return (1);
    else
         return (0);
}