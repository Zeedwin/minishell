#include "../includes/shell.h"

int test_builtin(char **s)
{
	if (s[0][0] == 'c')
	{
		if(s[0][1] == 'd')
			return(1);
	}
	else if (s[0][0] == 'e')
	{
		if(s[0][1] == 'c')
			if(s[0][2] == 'h')
				if (s[0][3] == 'o')
					if (s[1][0] == '-')
						if (s[1][1] == 'n')
							return(2);
	}
	else if (s[0][0] == 'e')
	{
		if(s[0][1] == 'x')
			if(s[0][2] == 'p')
				if (s[0][3] == 'o')
					if (s[0][4] == 'r')
						if (s[0][5] == 't')
							return(1);
	}
	else if (s[0][0] == 'p')
	{
		if(s[0][1] == 'w')
			if(s[0][2] == 'd')
				return(2);
	}
	else if (s[0][0] == 'u')
	{
		if(s[0][1] == 'n')
			if(s[0][2] == 's')
				if (s[0][3] == 'e')
					if (s[0][4] == 't')
						return(1);
	}
	else if (s[0][0] == 'e')
	{
		if(s[0][1] == 'n')
			if(s[0][2] == 'v')
				return(2);
	}
	else if (s[0][0] == 'e')
	{
		if(s[0][1] == 'x')
			if(s[0][2] == 'i')
				if (s[0][3] == 't')
					return(1);
	}
	return(0);
	
		
}

void token_builtin(t_lex *lex)
{
	int i;

	i = 0;
	while (i < ft_malloc(lex) - 2)
	{
		if (lex->supatok[i] == TOKEN_WORD)
		{
			if (test_builtin(lex->s[i]) == 1)
			{
				lex->supatok[i] = TOKEN_BUILTIN;
			}
			else if(test_builtin(lex->s[i]) == 2)
			{
				printf("ky$");
				lex->supatok[i] = TOKEN_BUILTIN_OUTP;
			}
		}
		i++;
	}
}