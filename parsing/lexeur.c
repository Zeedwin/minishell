#include "../includes/shell.h"


void	tokenrecon(t_token *tok)
{
	int i;

	i = 0;
	while(tok->data != NULL)
	{	
		printf("oui");
		//fflush(stdout);
		if (tok->data[i] == '|')
		{
			tok->type = TOKEN_PIPE;
		}
		else if (tok->data[i] == '>' || tok->data[i] == '<')
		{
			tok->type = TOKEN_REDIR;
		}
		else
		{
			tok->type = TOKEN_WORD;
		}
		printf("arg: %s type: %d\n", tok->data, tok->type);
		tok = tok->next;
	}   
}