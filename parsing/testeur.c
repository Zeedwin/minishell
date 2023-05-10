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
			lex->stoken[i] = TOKEN_PIPE;
		else if (lex->s1[i][j] == '>' || lex->s1[i][j] == '<')
			lex->stoken[i] = TOKEN_REDIR_S;
		else
			lex->stoken[i] = TOKEN_WORD;
		i++;
	}
}

int	check_vide2(char *s, int i)
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
	while (lex->s1[i])
	{
		if (lex->stoken[i] == TOKEN_PIPE)
			k++;
		else if (lex->stoken[i] == TOKEN_REDIR_S)
			k++;
		else if (lex->stoken[i] == TOKEN_WORD)
		{
			k++;
			while (lex->stoken[i] == TOKEN_WORD)
				i++;
			i--;
		}
		i++;
	}
	return (k + 2);
}

char	***separate_tok(t_var *var, t_lex *lex, char ***sf)
{
	int	i;
	int	j;
	int	k;

	(void)var;
	j = 0;
	i = 0;
	k = 0;
	sf = (char ***)malloc(sizeof(char **) * ft_malloc(lex));
	printf("malloc de %d\n", ft_malloc(lex));
	while (lex->s1[i])
	{
		if (lex->stoken[i] == TOKEN_PIPE || lex->stoken[i] == TOKEN_REDIR_S)
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
				i++;
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
				//free(lex->s1[i]);
			}
			k++;
		}
	}
	sf[k] = NULL;
	return (sf);
}

void	turbotokenizer(t_lex *lex)
{
	int	i;
	int	j;
	int	k;

	j = 0;
	i = 0;
	k = 0;
	while (lex->s[i])
	{
		if (lex->s[i][j][k] == '|')
			lex->supatok[i] = TOKEN_PIPE;
		else if (lex->s[i][j][k] == '<' || lex->s[i][j][k] == '>')
		{
			if (lex->s[i][j][k] == '>' && lex->s[i][j][k + 1] != '>')
				lex->supatok[i] = TOKEN_REDIR_S;
			else if (lex->s[i][j][k] == '<' && lex->s[i][j][k + 1] != '<')
				lex->supatok[i] = TOKEN_REDIR_E;
			else if (lex->s[i][j][k] == '>' && lex->s[i][j][k + 1] == '>')
				lex->supatok[i] = TOKEN_REDIR_S2;
			else if (lex->s[i][j][k] == '<' && lex->s[i][j][k + 1] == '<')
				lex->supatok[i] = TOKEN_REDIR_E2;
		}
		else if (test_builtin(lex->s[i]) == 1)
			lex->supatok[i] = TOKEN_BUILTIN;
		else if (test_builtin(lex->s[i]) == 2)
		{
			lex->supatok[i] = TOKEN_BUILTIN_OUTP;
		}
		else
		{
			lex->supatok[i] = TOKEN_WORD;
		}
		i++;
	}
}
