/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:52:39 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/25 12:42:51 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	parsing_syntax3(t_lex *lex, int i)
{
	if (lex->supatok[i] == TK_PIPE)
	{
		if ((i < ft_malloc(lex) - 3 && lex->supatok[i + 1] == TK_PIPE)
			|| lex->s[i + 1] == NULL)
		{
			printf("bash: syntax error near unexpected token '|'\n");
			return (0);
		}
	}
	if (lex->supatok[0] == TK_PIPE)
	{
		printf("bash: syntax error near unexpected token '|'\n");
		g_global.exitcode += 258;
		return (0);
	}
	return (1);
}

int	parsing_syntax2(t_lex *lex, int i)
{
	if (lex->supatok[i + 1] == TK_REDIR_S2)
	{
		printf("bash: syntax error near unexpected token '>>'\n");
		return (0);
	}
	if (lex->supatok[i + 1] == TK_REDIR_S)
	{
		printf("bash: syntax error near unexpected token '>'\n");
		return (0);
	}
	if (lex->supatok[i + 1] == TK_PIPE)
	{
		printf("bash: syntax error near unexpected token '|'\n");
		return (0);
	}
	return (1);
}

int	parsing_syntax1(t_lex *lex, int i)
{
	if (i + 1 >= ft_malloc(lex) - 2)
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		return (0);
	}
	if (lex->s[i + 1] == NULL && lex->supatok[i + 1] != TK_WORD)
	{
		printf("bash: syntax error near unexpected token 'newline'\n");
		return (0);
	}
	if (lex->supatok[i + 1] == TK_REDIR_E2)
	{
		printf("bash: syntax error near unexpected token '<<'\n");
		return (0);
	}
	if (lex->supatok[i + 1] == TK_REDIR_E)
	{
		printf("bash: syntax error near unexpected token '<'\n");
		return (0);
	}
	return (1);
}

int	parsing_syntax(t_lex *lex)
{
	int	i;

	i = 0;
	while (i < ft_malloc(lex) - 2)
	{
		if (lex->supatok[i] == TK_REDIR_E2
			|| lex->supatok[i] == TK_REDIR_E
			|| lex->supatok[i] == TK_REDIR_S
			|| lex->supatok[i] == TK_REDIR_S2)
		{
			if (parsing_syntax1(lex, i) == 0)
				return (0);
			if (parsing_syntax2(lex, i) == 0)
				return (0);
		}
		if (parsing_syntax3(lex, i) == 0)
			return (0);
		i++;
	}
	return (1);
}
