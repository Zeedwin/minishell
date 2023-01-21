#include "../includes/shell.h"


void	ft_lexeurinit(t_var *var, token *token, lexer *lex)
{
	lex->input = var->line;
	lex->pos = 0;
	lex->size = 0;
	while (lex->input[lex->pos])
	{
		if(lex->input[lex->pos] == "|")
		{
			token->type = TOKEN_PIPE;
			token->c = ft_strjoin(token->c, lex->input[lex->pos]);
		}
		if(lex->input[lex->pos] >= '!' && <= '~')
		{
			token->type = TOKEN_WORD;
			token->c;
		}
		if(lex->input[lex->pos] )
		{

		}
		lex->pos++;
	}
}

void first_lex(t_var *var)
{
	int i;

	i = 0;
	while ()
}
