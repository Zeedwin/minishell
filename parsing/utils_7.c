/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:57:24 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/01 14:34:54 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	mini_redir_s1(t_lex *lex, t_var *var)
{
	int	i;

	i = 0;
	while (lex->s[var->z][0] == NULL &&
			(lex->supatok[var->z + i] == TK_REDIR_S
			|| lex->supatok[var->z + i] == TK_REDIR_E
			|| lex->supatok[var->z + i] == TK_REDIR_S2
			|| lex->supatok[var->z + i] == TK_REDIR_E2))
	{
		if (lex->s[var->z + i + 2][1] != NULL)
		{
			lex->s[var->z][0] = ft_strdup(lex->s[var->z + i + 2][1]);
			var->c = var->z + i + 2;
		}
		i += 2;
	}
}
