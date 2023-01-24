#include "../includes/shell.h"

                                                                                                                                                                                                                                                                        

void tokenizer(t_lex *lex)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (lex->s1[i] != NULL)
	{
		if (lex->s1[i][j] == '|')
			lex->stoken[i] = TOKEN_PIPE;
		else if (lex->s1[i][j] == '>' || lex->s1[i][j] == '<')
			lex->stoken[i] = TOKEN_REDIR;
		else 
			lex->stoken[i] = TOKEN_WORD;
		i++;
	}
}

int check_vide2(char *s, int i)
{

	while (s[i] != '\0')
	{
		if (s[i] >= 33 && s[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}

int ft_malloc(char *s1)
{
	int i;
	int j;

	j = 1;
	i = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '|' || (s1[i] == '>' && s1[i + 1] != '>') || (s1[i] == '<' && s1[i + 1] == '<'))
		{
			i++;
			j++;
			if (check_vide2(s1, i) == 1)
				j++;
				//printf("uno %d\n", j);
		}
		else if ((s1[i] == '>' && s1[i + 1] == '>') || (s1[i] == '<' && s1[i + 1] == '<'))
		{
			i = i + 2;
			j++;
			if (check_vide2(s1, i) == 1)
				j++;
		}
		else 
			i++;
	}
	//printf("%d\n", j);
	return (j);
}

char ***separate_tok(t_var *var, t_lex *lex)
{
	char ***sf;
	
	int i;
	int j;
	int k;

	j = 0;
	i = 0;
	k = 0;
	sf = (char ***)malloc(sizeof(char **) * ft_malloc(var->line));
	printf("oui");
	fflush(stdout);
	while (lex->s1[i])
	{
		while (lex->stoken[i] != TOKEN_PIPE || lex->stoken[i] != TOKEN_REDIR)
		{
			i++;
		}
		sf[j] = malloc(sizeof(char *) * (i + 1));
		while (k <= i)
		{
			sf[j][k] = malloc(sizeof(char) * ft_strlen(lex->s1[k]));
			sf[j][k] = ft_strcpy(sf[j][k], lex->s1[k]);
			printf("%s\n", sf[j][k]);
			k++;
		}
		j++;
	}
	return (sf);
}