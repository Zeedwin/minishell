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

int	lexer3(t_lex *l, int i, int code)
{
	if (code == 1)
	{
		while (l->ss[i] != '\0' && l->ss[i] != ' '
			&& l->ss[i] != '|' && l->ss[i] != '>'
			&& l->ss[i] != '<')
		{
			if (l->ss[i] == '"')
				i = lexer6(l, i, 0);
			else if (l->ss[i] == '\'')
				i = lexer6(l, i, 1);
			else
				i++;
		}
		l->ss = lexeur2(l, i);
		return (i);
	}
	return (i);
}

char	*lexeur2(t_lex *lex, int i)
{
	lex->s1[lex->x] = ft_substr(lex->ss, 0, i);
	lex->x++;
	lex->ss += i;
	return (lex->ss);
}

int	lexer1(t_lex *l)
{
	int	i;

	i = 0;
	if (l->x < l->y)
	{
		while (l->ss[i] == ' ' && l->ss[i] != '\0')
		{
			i++;
			if (l->ss[i] != ' ')
			{	
				l->ss += i;
				lexer1(l);
				return (1);
			}
		}
		i = lexer5(l, i);
		lexer1(l);
		l->s1[l->x] = NULL;
		return (1);
	}
	l->s1[l->x] = NULL;
	return (1);
}

char	*init_tab2(char *s, char **env, t_var *var)
{
	t_ini	ini;
	char	*s2;
	char	*s3;

	(void)env;
	(void)var;
	s2 = space_change(s);
	if (error_quote(s2, &ini) == 0)
	{
		printf("quote open : error\n");
		s3 = ft_strdup("");
		free(s2);
		return (s3);
	}
	else if (point(s2) == 1 || point2(s2) == 0)
	{
		s3 = del_brak2(s2);
		printf("bash : %s: command not found\n", s);
		s3 = ft_strdup("");
		free(s2);
		return (s3);
	}
	s2 = change_tab(s2);
	s2 = del_par_com(s2);
	return (s2);
}

void	init_tab(t_lex *lex, char *s, char **env, t_var *var)
{
	char	*s2;
	char	*s3;

	s3 = init_tab2(s, env, var);
	s = ft_strdup(s3);
	lex->s1 = ft_calloc((count(s3, var) + 1), sizeof(char *));
	lex->stoken = ft_calloc((count(s3, var) + 1), sizeof(int));
	lex->supatok = ft_calloc((count(s3, var) + 1), sizeof(int));
	lex->x = 0;
	lex->c = 0;
	lex->y = count(s3, var);
	lex->ss = malloc(sizeof(char) * (ft_strlen(s3) + 1));
	lex->ss = ft_strcpy(lex->ss, s3);
	s2 = lex->ss;
	lexer1(lex);
	lex->s1[count(s3, var)] = NULL;
	lex->stoken[count(s3, var)] = TK_FIN;
	lex->supatok[count(s3, var)] = TK_FIN;
	free(s2);
	free(s3);
	free(s);
}
