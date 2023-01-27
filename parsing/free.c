#include "../includes/shell.h"

void free_2(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		i++;
	}
	free(s);
}

void free_3(char ***s)
{
	int i;

	i = 0;
	while (s[i])
	{
		free_2(s[i]);
		i++;
	}
	free(s);
}

void free_final(t_lex *lex)
{
	free_2(lex->s1);
	//free(lex->stoken);
	free_3(lex->s);
	//free(lex->supatok);
}
