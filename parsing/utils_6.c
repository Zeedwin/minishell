/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 15:00:12 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/17 16:34:12 by hdelmann         ###   ########.fr       */
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
	lex->supatok = ft_calloc((lex->y + 2), sizeof(int));
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