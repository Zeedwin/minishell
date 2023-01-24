#include "../includes/shell.h"

int count2(int i, char *s, int code)
{
	if (code == 0)
	{
		while (s[i] != '"' && s[i] != '\0')// && s[i] != '\'')
		{
			i++;
			if (s[i - 1] == '\\' && s[i] == '"')
				i++;
		}
	}
	if (code == 3)
	{
		while (s[i] != '\'' && s[i] != '\0') //&& s[i] != '\'')
		{
			i++;
			if (s[i - 1] == '\\' && s[i] == '\'')
				i++;
		}
	}
	if (code == 1)
	{
		while (s[i] != '\0' && s[i] == ' ')
		{
			i++;
		}
	}
	if (code == 2)
	{
		while (s[i] != ' ' && (s[i] != '"' || (s[i] == '"' && s[i - 1] == '\\')) && s[i] != '\0' 
			&& (s[i] != '\'' || (s[i] == '\'' && s[i - 1] == '\\')) 
			&& (s[i] != '|' || (s[i] == '|' && s[i - 1] == '\\'))
			&& (s[i] != '>' || (s[i] == '>' && s[i - 1] == '\\'))
			&& (s[i] != '<' || (s[i] == '<' && s[i - 1] == '\\')))

		{
			i++;
		}
	}
	return (i);
}

int count(char *s)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"' && (i == 0 || s[i - 1] != '\\'))
		{
			j++;
			i++;
			i = count2(i, s, 0);
			i++;
		}
		else if (s[i] == '\'' && (i == 0 || s[i - 1] != '\\'))
		{
			j++;
			i++;
			i = count2(i, s, 3);
			i++;
		}
		else if (s[i] == ' ')
		{
			i = count2(i, s , 1);
		}
		else if (s[i] == '|' || (s[i] == '<' && s[i + 1] != '<')
				|| (s[i] == '>' && s[i + 1] != '>'))
		{
			i++;
			j++;
		}
		else if ((s[i] == '<' && s[i + 1] == '<') 
				|| (s[i] == '>' && s[i + 1] == '>'))
		{
			i = i + 2;
			j++;
		}
		else
		{
			j++;
			i = count2(i, s, 2);
		}
	}
	return(j);
}

int check_vide(char *s)
{
	int i;
	
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= 33 && s[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}

char *lexer2(char *s, t_lex *lex, int i)
{
	lex->s1[lex->x] = ft_substr(s, 0, i);
	lex->x++;
	s = ft_substr(s, i, ft_strlen(s));
	return (s);
}

int lexer3(int i, char *s, int code)
{
	if (code == 0)
	{
		i++;
		while (1)
		{
			if (s[i] == '"' && s[i - 1] != '\\')
				break;
			i++;
		}
		i++;
	}
	if (code == 2)
	{
		i++;
		while (1)
		{
			if (s[i] == '\'' && s[i - 1] != '\\')
				break;
			i++;
		}
		i++;
	}
	if (code == 1)
	{
		while (s[i] != '\0' && s[i] != ' ' && (s[i] != '"' || (s[i] == '"' && s[i - 1] == '\\'))
				&& (s[i] != '\'' || (s[i] == '\'' && s[i - 1] == '\\'))
				&& (s[i] != '|' || (s[i] == '|' && s[i - 1] == '\\'))
				&& (s[i] != '>' || (s[i] == '>' && s[i - 1] == '\\'))
				&& (s[i] != '<' || (s[i] == '<' && s[i - 1] == '\\')))
		{
				i++;
		}
	}
	return (i);
}

int lexer1(char *s, t_lex *lex)
{
	int i;

	i = 0;
	if (lex->x <= lex->y)
	{
		while (s[i] == ' ' && s[i] != '\0')
		{
			i++;
			if (s[i] != ' ')
			{	
				s = ft_substr(s, i, ft_strlen(s));	
				lexer1(s, lex);
				return (1);
			}
		}
		if (s[i] == '"' && ((i == 0 || s[i - 1] != '\\')))
		{
			i = lexer3(i, s, 0);
			s = lexer2(s, lex, i);
		}
		else if (s[i] == '|' || (s[i] == '<' && s[i + 1] != '<')
				|| (s[i] == '>' && s[i + 1] != '>'))
		{
			i++;
			s = lexer2(s, lex, i);
		}
		else if (s[i] == '\'' && ((i == 0 || s[i - 1] != '\\')))
		{
			i = lexer3(i, s, 2);
			s = lexer2(s, lex, i);
		}
		else if ((s[i] == '<' && s[i + 1] == '<') 
				|| (s[i] == '>' && s[i + 1] == '>'))
		{
			i = i + 2;
			s = lexer2(s, lex, i);
		}
		else
		{
			i = lexer3(i, s, 1);
			s = lexer2(s, lex, i);
		}
		lex->rap++;
		lexer1(s, lex);
		return (1);
	}
	return (1);
}

char *suppr_pos(char *s, int pos)
{
	char *s1;
	int i;
	int j;

	s1 = malloc(sizeof(char) * ft_strlen(s));
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i != pos)
		{
			s1[j] = s[i];
			j++;
		}
		i++;
	}
	s1[j] = '\0';
	return (s1);
}

char *del_if_quote(char *s)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"' && (i == 0 || s[i - 1] != '\\'))
		{
			j = i;
			k++;
		}
		i++;
	}
	if (k % 2 == 0)
		return (s);
	else 
		s = suppr_pos(s, j);
	return (s);
}

char *del_if_quote2(char *s)
{
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'' && (i == 0 || s[i - 1] != '\\'))
		{
			j = i;
			k++;
		}
		i++;
	}
	if (k % 2 == 0)
		return (s);
	else 
		s = suppr_pos(s, j);
	return (s);
}

char *del_par_com(char *s)
{
	int i;
	int j;
	char *s1;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '#')
			break;
		if (s[i] != ')' && s[i] != '(')
			j++;
		i++;
	}
	s1 = malloc(sizeof(char) * (j + 2));
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '#')
			break;
		if (s[i] != ')' && s[i] != '(')
		{
			s1[j] = s[i];
			j++;
		}
		i++;
	}
	s1[j] = '\0';
	return (s1);
}


void init_tab(t_lex *lex, char *s)
{
	s = del_par_com(s);
	s = del_if_quote(s);
	s = del_if_quote2(s);
	lex->s1 = malloc((count(s) + 1) * sizeof(char *));
	lex->stoken = malloc((count(s) + 1) * sizeof(int));
	lex->x = 0;
	lex->c = 0;
	lex->rap = 0;
	lex->y = count(s);
	lexer1(s, lex);
	lex->s1[count(s)] = NULL;
	/*int	j;
	j = 0;
	while (lex.s1[j])
	{
		printf("-> %s\n", lex.s1[j]);
		j++;
	}
	//printf("%s\n", lex.s1[count(s) - 1]);*/
}

