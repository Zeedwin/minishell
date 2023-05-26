/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexeur2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodelmann <hugodelmann@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:24:37 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/25 18:35:58 by hugodelmann      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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
	/*else if (l->ss[i] == '\'')
		lexer4(l, i);*/
	else if ((l->ss[i] == '<' && l->ss[i + 1] == '<')
		|| (l->ss[i] == '>' && l->ss[i + 1] == '>'))
		(n(), i = i + 2, l->ss = lexeur2(l, i));
	else
		i = lexer3(l, i, 1);
	return (i);
}
