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

int ft_malloc(t_lex *lex)
{
	int i;
	int k;

	i = 0;
	k = 0;
	while (lex->s1[i])
	{
		if (lex->stoken[i] == TOKEN_PIPE)
		{
			k++;
		}
		else if (lex->stoken[i] == TOKEN_REDIR)
		{
			k++;
		}
		else if (lex->stoken[i] == TOKEN_WORD)
		{
			k++;
			while (lex->stoken[i] == TOKEN_WORD)
			{
				i++;
			}
			i--;
		}
		i++;
		//printf("oui");
	}
	return (k + 2);
}


/*int linecopy(char **s1, char **dest, int j, int i)
{
	int k;

	k = 0;
	//printf("j:%d and i:%d\n", j, i);
	while (j != i)
	{
		//printf("COPY %d: %s\n", j, s1[j]);		
		dest[k] = malloc(sizeof(char) * ft_strlen(s1[j]) + 1);
		ft_strlcpy(dest[k], s1[j], ft_strlen(s1[j]) + 1);
		//printf("DEST %d: %s\n", k, dest[k]);
		//dest[k] = s1[j];
		k++;
		j++;
	}
	dest[k] = NULL;
	return (1);
}*/


char ***separate_tok(t_var *var, t_lex *lex)
{
	char ***sf;
	
	int i;
	int j;
	int k;

	(void)var;
	j = 0;
	i = 0;
	k = 0;
	sf = (char ***)malloc(sizeof(char **) * ft_malloc(lex));
	while (lex->s1[i])
	{
		if (lex->stoken[i] == TOKEN_PIPE || lex->stoken[i] == TOKEN_REDIR)
		{
			sf[k] = malloc(sizeof(char *) * 2);
			sf[k][0] = malloc(sizeof(char) * (ft_strlen(lex->s1[i]) + 1));
			sf[k][0] = ft_strcpy(sf[k][0], lex->s1[i]);
			sf[k][1] = NULL;
			k++;
			i++;
		}
		else if (lex->stoken[i] == TOKEN_WORD)
		{
			j = i;
			while (lex->stoken[i] == TOKEN_WORD && lex->s1[i])
			{
				i++;
			}
			sf[k] = malloc(sizeof(char *) * (i - j + 1));
			i = j;
			j = 0;
			while (lex->stoken[i] == TOKEN_WORD && lex->s1[i])
			{
				sf[k][j] = malloc(sizeof(char) * (ft_strlen(lex->s1[i]) + 1));
				sf[k][j] = ft_strcpy(sf[k][j], lex->s1[i]);
				j++;
				i++;
				sf[k][j] = NULL;
			}
			k++;
		}
	}
	sf[k] = NULL;
	return (sf);
}

