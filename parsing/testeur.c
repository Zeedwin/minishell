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
	int k;

	i = 0;
	k = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == '|')
			k++;
		i++;
	}
	printf("%d\n", k + 2);
	
	return (k + 2);
}


int linecopy(char **s1, char **dest, int j, int i)
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
	//printf("oui");
	//fflush(stdout);
	// "ls" "-l" "|" "cat" "-e" NULL
	while (lex->s1[i])
	{
		if (ft_strncmp(lex->s1[i], "|", 1) == 0)
		{
			//printf ("malloc i - j %d and k: %d\n", i - j, k);
			sf[k] = malloc(sizeof(char *) * (i - j + 1));
			linecopy(lex->s1, sf[k], j, i);
			//printf("ICIIIII %s\n", sf[k][0]);
			j = i + 1;
			k++;
		}
		i++;
	}
	sf[k] = malloc(sizeof(char *) * (i - j + 1));
	linecopy(lex->s1, sf[k], j, i);
	k++;
	sf[k] = NULL;
	return (sf);
}

