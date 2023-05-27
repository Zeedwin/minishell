/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testeur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:39:58 by hdelmann          #+#    #+#             */
/*   Updated: 2023/04/27 10:39:58 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	tokenizer(t_lex *lex)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (lex->s1[i] != NULL)
	{
		if (lex->s1[i][j] == '|')
			lex->stoken[i] = TK_PIPE;
		else if (lex->s1[i][j] == '>' || lex->s1[i][j] == '<')
			lex->stoken[i] = TK_REDIR_S;
		else
			lex->stoken[i] = TK_WORD;
		i++;
	}
}

int	check_empty2(char *s, int i)
{
	while (s[i] != '\0')
	{
		if (s[i] >= 33 && s[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}

int	ft_malloc(t_lex *lex)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (lex->s1[i] != NULL)
	{
		if (lex->stoken[i] == TK_PIPE)
			k++;
		else if (lex->stoken[i] == TK_REDIR_S)
			k++;
		else if (lex->stoken[i] == TK_WORD)
		{
			k++;
			while (lex->stoken[i] != TK_FIN && lex->stoken[i] == TK_WORD)
				i++;
			i--;
		}
		i++;
	}
	return (k + 2);
}

char	***separate_tok(t_var *v, t_lex *lex, char ***sf)
{
	(n(), v->p = 0, v->k = 0, v->j = 0,
		sf = (char ***)malloc(sizeof(char **) * ft_malloc(lex)));
	while (lex->s1[v->p])
	{
		if (lex->stoken[v->p] == TK_PIPE || lex->stoken[v->p] == TK_REDIR_S)
			(n(), sf[v->k] = malloc(sizeof(char *) * 2), sf[v->k][0] =
				malloc(sizeof(char) * (ft_strlen(lex->s1[v->p]) + 1)),
				sf[v->k][0] = ft_strcpy(sf[v->k][0], lex->s1[v->p]),
				sf[v->k][1] = NULL, v->k++, v->p++);
		else if (lex->stoken[v->p] == TK_WORD)
		{
			v->j = v->p;
			while (lex->stoken[v->p] == TK_WORD && lex->s1[v->p])
				v->p++;
			(n(), sf[v->k] = malloc(sizeof(char *) * (v->p - v->j + 1)),
				v->p = v->j, v->j = 0);
			while (lex->stoken[v->p] == TK_WORD && lex->s1[v->p])
				(n(), sf[v->k][v->j] = malloc(sizeof(char) * (ft_strlen(lex
					->s1[v->p]) + 1)), sf[v->k][v->j] = ft_strcpy(sf[v->k][v->
					j], lex->s1[v->p]), v->j++, v->p++, sf[v->k][v->j] = NULL);
			v->k++;
		}
	}
	sf[v->k] = NULL;
	return (sf);
}

void	turbotokenizer(t_lex *lex)
{
	int	i;

	i = 0;
	while (lex->s[i])
	{
		if (lex->s[i][0][0] == '|')
			lex->supatok[i] = TK_PIPE;
		else if (lex->s[i][0][0] == '<' || lex->s[i][0][0] == '>')
			turbotokenizer1(lex, i);
		else if (test_builtin(lex->s[i]) == 1)
			lex->supatok[i] = TK_BUILTIN;
		else if (test_builtin(lex->s[i]) == 2)
			lex->supatok[i] = TK_BOUT;
		else
			lex->supatok[i] = TK_WORD;
		i++;
	}
}
