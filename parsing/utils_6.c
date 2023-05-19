/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:00:12 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/19 14:11:53 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	cpy3truc1(t_var *v, t_lex *lex)
{
	v->j = v->p;
	while (lex->stoken[v->p] == TK_WORD && lex->s1[v->p])
		v->p++;
}

void	turbotokenizer2(t_lex *lex)
{
	int	i;

	i = 0;
	free(lex->supatok);
	lex->supatok = ft_calloc((lex->y + 3), sizeof(int));
	while (lex->s[i])
	{
		if (lex->s[i][0][0] == '|')
			lex->supatok[i] = TK_PIPE;
		else if (lex->s[i][0][0] == '<' || lex->s[i][0][0] == '>')
			turbotokenizer1(lex, i);
		else if (test_builtin(lex->s[i]) == 1)
			lex->supatok[i] = TK_BUILTIN;
		else if (test_builtin(lex->s[i]) == 2)
			lex->supatok[i] = TK_BUILTIN_OUTP;
		else
			lex->supatok[i] = TK_WORD;
		i++;
	}
}

int	ft_malloc2(t_lex *lex)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (i < ft_malloc(lex))
	{
		if (lex->supatok[i] == TK_PIPE)
			k++;
		else if (lex->supatok[i] == TK_REDIR_S)
			k++;
		else if (lex->supatok[i] == TK_WORD)
		{
			k++;
			while (lex->supatok[i] == TK_WORD)
				i++;
			i--;
		}
		i++;
	}
	return (k + 2);
}

int		incr_i(t_lex *lex, t_var *var)
{
	if (lex->supatok[var->z + var->i + 2] == TK_REDIR_S
		|| lex->supatok[var->z + var->i + 2] == TK_REDIR_E
		|| lex->supatok[var->z + var->i + 2] == TK_REDIR_S2
		|| lex->supatok[var->z + var->i + 2] == TK_REDIR_E2)
	{
		var->i += 2;
		return (0);
	}
	return (-1);
}
