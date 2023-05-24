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

char	*lexeur2(char *s, t_lex *lex, int i)
{
	lex->s1[lex->x] = ft_substr(s, 0, i);
	lex->x++;
	s += i;
	return (s);
}

int	lexer1(char *s, t_lex *lex)
{
	int	i;

	i = 0;
	if (lex->x < lex->y)
	{
		while (s[i] == ' ' && s[i] != '\0')
		{
			i++;
			if (s[i] != ' ')
			{	
				s += i;
				lexer1(s, lex);
				return (1);
			}
		}
		if (s[i] == '"' )
		{
			i++;
			while (1)
			{
				if (s[i] == '"')
					break ;
				i++;
			}
			i++;
			s = lexeur2(s, lex, i);
		}
		else if (s[i] == '|' || (s[i] == '<' && s[i + 1] != '<')
			|| (s[i] == '>' && s[i + 1] != '>'))
		{
			i++;
			s = lexeur2(s, lex, i);
		}
		else if (s[i] == '\'')
		{
			i++;
			while (1)
			{
				if (s[i] == '\'')
					break ;
				i++;
			}
			i++;
			s = lexeur2(s, lex, i);
		}
		else if ((s[i] == '<' && s[i + 1] == '<')
			|| (s[i] == '>' && s[i + 1] == '>'))
		{
			i = i + 2;
			s = lexeur2(s, lex, i);
		}
		else
		{
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '"'
				&& s[i] != '\'' && s[i] != '|' && s[i] != '>' && s[i] != '<' )
				i++;
			s = lexeur2(s, lex, i);
		}
		lexer1(s, lex);
		lex->s1[lex->x] = NULL;
		return (1);
	}
	lex->s1[lex->x] = NULL;
	return (1);
}

void	init_tab(t_lex *lex, char *s, char **env, t_var *var)
{
	char	*s2;
	t_ini	ini;

	if (point(s) == 1)
	{
		printf("bash : %s: command not found\n", s);
		s = ft_strdup("");
	}
	if (error_quote(s) == 0)
	{
		printf("quote open : error\n");
		s = ft_strdup("");
	}
	s = space(s);
	s = change_tab(s);
	s = del_par_com(s);
	s = replace_dol_(s, var->last_err_com, &ini);
	s = dollars_ch(s, env);
	lex->s1 = ft_calloc((count(s, var) + 1), sizeof(char *));
	lex->stoken = ft_calloc((count(s, var) + 1), sizeof(int));
	lex->supatok = ft_calloc((count(s, var) + 1), sizeof(int));
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
