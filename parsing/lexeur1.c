/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:15:23 by hdelmann          #+#    #+#             */
/*   Updated: 2023/04/27 10:15:23 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	count2(int i, char *s, int code)
{
	if (code == 0)
	{
		while (s[i] != '"' && s[i] != '\0')
		{
			i++;
			if (s[i - 1] == '\\' && s[i] == '"')
				i++;
		}
	}
	if (code == 3)
	{
		while (s[i] != '\'' && s[i] != '\0')
		{
			i++;
			if (s[i - 1] == '\\' && s[i] == '\'')
				i++;
		}
	}
	if (code == 1)
		while (s[i] != '\0' && s[i] == ' ')
			i++;
	if (code == 2)
		while (s[i] != ' ' && s[i] != '"' && s[i] != '\0' && s[i] != '\''
			&& s[i] != '|' && s[i] != '>' && s[i] != '<' )
			i++;
	return (i);
}

int	count(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			j++;
			i++;
			i = count2(i, s, 0);
			i++;
		}
		else if (s[i] == '\'')
		{
			j++;
			i++;
			i = count2(i, s, 3);
			i++;
		}
		else if (s[i] == ' ')
			i = count2(i, s, 1);
		else if ((s[i] == '|') || (s[i] == '<' && s[i + 1] != '<')
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
	return (j);
}

int	check_vide(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= 33 && s[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}

char	*lexer2(char *s, t_lex *lex, int i)
{
	lex->s1[lex->x] = ft_substr(s, 0, i);
	lex->x++;
	s = ft_substr(s, i, ft_strlen(s));
	//free(lex->s1);
	return (s);
}

int	lexer3(int i, char *s, int code)
{
	if (code == 0)
	{
		i++;
		while (1)
		{
			if (s[i] == '"')
				break ;
			i++;
		}
		i++;
	}
	if (code == 2)
	{
		i++;
		while (1)
		{
			if (s[i] == '\'')
				break ;
			i++;
		}
		i++;
	}
	if (code == 1)
		while (s[i] != '\0' && s[i] != ' ' && s[i] != '"'
			&& s[i] != '\'' && s[i] != '|' && s[i] != '>' && s[i] != '<' )
				i++;
	return (i);
}

int	lexer1(char *s, t_lex *lex)
{
	int	i;

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
		if (s[i] == '"' )
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
		else if (s[i] == '\'')
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
		//free(s);
		return (1);
	}
	free(s);
	return (1);
}

char	*suppr_pos(char *s, int pos)
{
	char	*s1;
	int		i;
	int		j;

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
	free(s);
	return (s1);
}

char	*del_if_quote(char *s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
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

char	*del_if_quote2(char *s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
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

char	*del_par_com(char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '#')
		{
			s = ft_realloc(s, i);
			s[i] = '\0';
		}
		i++;
	}
	return (s);
}

char	*change_tab(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				i++;
		}
		if (s[i] == '\t')
			s[i] = ' ';
		i++;
	}
	return (s);
}

char	*space(char *s)
{
	if (s[0] == '$')
	{
		s = ft_strjoin(" ", s);
		return (s);
	}
	return (s);
}

int point(char *s)
{
	if (ft_strlen(s) == 2 && s[0] == '.' && s[1] == '.')
		return (1);
	if (ft_strlen(s) == 1 && s[0] == '.')
		return (1);
	return (2);
}

void	init_tab(t_lex *lex, char *s, char **env, t_var *var)
{
	char	*s1;

	s1 = malloc(sizeof(char));
	s1[0] = '\0';
	if (point(s) == 1)
	{
		printf("bash : %s: command not found\n", s);
		s = ft_strdup(s1);
	}
	s = space(s);
	s = change_tab(s);
	s = del_if_quote(s);
	s = del_par_com(s);
	s = del_if_quote2(s);
	s = replace_dol_(s, var->last_err_com);
	s = dollars_ch(s, env);
	lex->s1 = malloc((count(s) + 1) * sizeof(char *));
	lex->stoken = malloc((count(s) + 1) * sizeof(int));
	lex->supatok = malloc((count(s) + 1) * sizeof(int));
	lex->x = 0;
	memset(lex->stoken, 0, (count(s) + 1) * sizeof(int));
	lex->c = 0;
	lex->rap = 0;
	lex->y = count(s);
	lexer1(s, lex);
	lex->s1[count(s)] = NULL;
	free(s1);
	free(s);
}
