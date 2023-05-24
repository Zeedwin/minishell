/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_gen2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:51:32 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/24 12:53:47 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	pro(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (lex->s[var->z + 1] == NULL)
	{
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
		{
			if (var->z > 0 && (var->last_pipe == 1
					|| lex->supatok[var->z - 1] == TK_PIPE))
				dup2(var->fd, STDIN_FILENO);
			executeur_final(lex->s[var->z], g_global.cpyenv, var, lex);
		}
		else
		{
			parent_pro(lex, var, pip);
			return (0);
		}
	}
	else
		var->z++;
	return (1);
}
