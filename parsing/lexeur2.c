/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:24:37 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/27 12:44:10 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	lexer6(t_lex *l, int i, int code)
{
	if (code == 0)
	{
		i++;
		while (l->ss[i] != '\0' && l->ss[i] != '\"')
			i++;
		i++;
	}
	if (code == 1)
	{
		i++;
		while (l->ss[i] != '\0' && l->ss[i] != '\'')
			i++;
		i++;
	}
	return (i);
}

int	lexer4(t_lex *l, int i)
{
	i++;
	while (1)
	{
		if (l->ss[i] != '\0' && l->ss[i] == '\'')
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
		(n(), i++, l->ss = lexeur2(l, i));
	else if ((l->ss[i] == '<' && l->ss[i + 1] == '<')
		|| (l->ss[i] == '>' && l->ss[i + 1] == '>'))
		(n(), i = i + 2, l->ss = lexeur2(l, i));
	else
		i = lexer3(l, i, 1);
	return (i);
}
