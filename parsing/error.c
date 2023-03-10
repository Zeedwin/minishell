#include "../includes/shell.h"

int parsing_syntax(t_lex *lex)
{
	int i;

	i = 0;
	while (i < ft_malloc(lex) - 2)
	{
		if (lex->supatok[i] == TOKEN_REDIR_E2 || lex->supatok[i] == TOKEN_REDIR_E
			|| lex->supatok[i] == TOKEN_REDIR_S || lex->supatok[i] == TOKEN_REDIR_S2)
		{
			if (lex->s[i + 1] == NULL && lex->supatok[i + 1] != TOKEN_WORD)
			{
				///printf("== %s\n", lex->s[i][0]);
				//fflush(stdout);
				printf("bash: syntax error near unexpected token 'newline'\n");
				return(0);
			}
			if (lex->supatok[i + 1] == TOKEN_REDIR_E2)
			{
				printf("bash: syntax error near unexpected token '<<'\n");
				return(0);
			}
			if (lex->supatok[i + 1] == TOKEN_REDIR_E)
			{
				printf("bash: syntax error near unexpected token '<'\n");
				return(0);
			}
			if (lex->supatok[i + 1] == TOKEN_REDIR_S2)
			{
				printf("bash: syntax error near unexpected token '>>'\n");
				return(0);
			}
			if (lex->supatok[i + 1] == TOKEN_REDIR_S)
			{
				printf("bash: syntax error near unexpected token '>'\n");
				return(0);
			}
			if (lex->supatok[i + 1] == TOKEN_PIPE)
			{
				printf("bash: syntax error near unexpected token '|'\n");
				return(0);
			}
		}
		if (lex->supatok[i] == TOKEN_PIPE)
		{
			if (i < ft_malloc(lex) - 3 && lex->supatok[i + 1] == TOKEN_PIPE)
			{
				printf("bash: syntax error near unexpected token '|'\n");
				return(0);
			}
		}

		if (lex->supatok[0] == TOKEN_PIPE)
		{
			printf("bash: syntax error near unexpected token '|'\n");
			return(0);
		}
		i++;
	}
	return (1);
}