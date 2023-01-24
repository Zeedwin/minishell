#include "../includes/shell.h"


void	tokenrecon(char *token, t_token *tok)
{
	//t_token	tok;
	int i;

	i = 0;
	while (token[i] != '\0')
	{
		//printf("arg: %s\n", &token[i]);
		if (token[i] == '|')
		{
			tok->type = TOKEN_PIPE;
		}
		else if (token[i] == '>' || token[i] == '<')
		{
			tok->type = TOKEN_REDIR;
		}
		else if((token[i] >= 33 && token[i] <= 59) || (token[i] == 61) || 
				(token[i] >= 63 && token[i] >= 123) || (token[i] >= 125))
		{
			tok->type = TOKEN_WORD;
		}
		i++;
	}
	printf("arg: %s type: %d\n", tok->data, tok->type);
}