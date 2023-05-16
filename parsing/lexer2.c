/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:07:59 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/16 12:08:29 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	i_lexer(char *s, t_lex *lex, int code)
{
	if (code == 0)
	{
		lex->ii++;
		while (1)
		{
			if (s[lex->ii] == '"')
				break ;
			lex->ii++;
		}
		lex->ii++;
	}
	if (code == 1)
	{
		lex->ii++;
		while (1)
		{
			if (s[lex->ii] == '\'')
				break ;
			lex->ii++;
		}
		lex->ii++;
	}
}
