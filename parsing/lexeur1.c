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

char	*lexeur2(char *s, t_lex *lex, int i, int code)
{
	if (code == 0)
		i_lexer(s, lex, 0);
	if (code == 1)
		i++;
	if (code == 2)
		i_lexer(s, lex, 1);
	if (code == 3)
		i = i + 2;
	if (code == 4)
	{
		while (s[i] != '\0' && s[i] != ' '
			&& s[i] != '"' && s[i] != '\''
			&& s[i] != '|' && s[i] != '>' && s[i] != '<')
				i++;
	}
	lex->s1[lex->x] = ft_substr(s, 0, i);
	lex->x++;
	s += i;
	return (s);
}

int	lexer2(char *s, t_lex *lex)
{
	while (s[lex->ii] == ' ' && s[lex->ii] != '\0')
	{
		lex->ii++;
		if (s[lex->ii] != ' ')
		{	
			s += lex->ii;
			lexer1(s, lex);
			return (1);
		}
	}
	return (0);
}

int	lexer1(char *s, t_lex *lex)
{
	lex->ii = 0;
	if (lex->x < lex->y)
	{
		if (lexer2(s, lex) == 1)
			return (1);
		if (s[lex->ii] == '"' )
			s = lexeur2(s, lex, lex->ii, 0);
		else if (s[lex->ii] == '|' || (s[lex->ii] == '<'
				&& s[lex->ii + 1] != '<') || (s[lex->ii] == '>'
				&& s[lex->ii + 1] != '>'))
			s = lexeur2(s, lex, lex->ii, 1);
		else if (s[lex->ii] == '\'')
			s = lexeur2(s, lex, lex->ii, 2);
		else if ((s[lex->ii] == '<' && s[lex->ii + 1] == '<')
			|| (s[lex->ii] == '>' && s[lex->ii + 1] == '>'))
			s = lexeur2(s, lex, lex->ii, 3);
		else
			s = lexeur2(s, lex, lex->ii, 4);
		lexer1(s, lex);
		lex->s1[lex->x] = NULL;
		return (1);
	}
	lex->s1[lex->x] = NULL;
	return (1);
}

char	*init_char(char *s, t_lex *lex, t_var *var, char **env)
{
	char	*s1;

	s1 = ft_calloc(1, sizeof(char));
	s1[0] = '\0';
	s = space(s);
	s = change_tab(s);
	s = del_par_com(s);
	s = replace_dol_(s, var->last_err_com);
	s = dollars_ch(s, env);
	if (point(s) == 1)
	{
		printf("bash : %s: command not found\n", s);
		s = ft_strdup(s1);
	}
	if (error_quote(s) == 0)
	{
		printf("quote open : error\n");
		s = ft_strdup(s1);
	}
	lex->s1 = ft_calloc((count(s, var) + 1), sizeof(char *));
	lex->stoken = ft_calloc((count(s, var) + 1), sizeof(int));
	lex->supatok = ft_calloc((count(s, var) + 1), sizeof(int));
	free(s1);
	return (s);
}

void	init_tab(t_lex *lex, char *s, char **env, t_var *var)
{
	char	*s2;

	s = init_char(s, lex, var, env);
	lex->x = 0;
	lex->c = 0;
	lex->y = count(s, var);
	s2 = malloc(sizeof(char) * (ft_strlen(s) + 1));
	s2 = ft_strcpy(s2, s);
	lexer1(s2, lex);
	lex->s1[count(s, var)] = NULL;
	lex->stoken[count(s, var)] = TK_FIN;
	lex->supatok[count(s, var)] = TK_FIN;
	free(s);
	free(s2);
}
