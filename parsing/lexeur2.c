/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:24:37 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/24 12:31:43 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	lexer4(t_lex *l, int i)
{
	i++;
	while (1)
	{
		if (l->ss[i] == '\'')
			break ;
		i++;
	}
	i++;
	l->ss = lexeur2(l, i);
	return (i);
}

int	lexer5(t_lex *l, int i)
{
	if (l->ss[i] == '|' || (l->ss[i] == '<' && l->ss[i + 1] != '<')
		|| (l->ss[i] == '>' && l->ss[i + 1] != '>'))
		(norm(), i++, l->ss = lexeur2(l, i));
	else if (l->ss[i] == '\'')
		lexer4(l, i);
	else if ((l->ss[i] == '<' && l->ss[i + 1] == '<')
		|| (l->ss[i] == '>' && l->ss[i + 1] == '>'))
		(norm(), i = i + 2, l->ss = lexeur2(l, i));
	else
		i = lexer3(l, i, 1);
	return (i);
}
