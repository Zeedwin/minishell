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

void free_1(int **s, t_lex *lex)
{
	int i;
	int j;

	i = 0;
	j = count_pipe(lex->supatok, lex) + 1;
	while (i < j)
	{
		free(s[i]);
		i++;
	}
}

void free_final(t_lex *lex, t_pipe *pip)
{
	(void)pip;
	free_2(lex->s1);
	//free_1(pip->pipe, lex);
	//free(lex->stoken);
	free_3(lex->s);
	//free(lex->supatok);
}
