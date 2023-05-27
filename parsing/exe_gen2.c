/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_gen2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:51:32 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/27 12:20:49 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	child_pro(t_lex *lex, t_var *var)
{
	if (var->z > 2 && (lex->supatok[var->z - 3] == TK_REDIR_S
			|| lex->supatok[var->z - 3] == TK_REDIR_S2)
		&& lex->supatok[var->z - 1] == TK_PIPE)
	{
		close(var->fd);
		var->fd = open("tmp/tmp.txt", O_CREAT
				| O_TRUNC | O_RDONLY, 0777);
		dup2(var->fd, STDIN_FILENO);
	}
	else if (((var->z > 3 && lex->supatok[var->z - 4] == TK_PIPE)
			|| var->z - 3 == 0)
		&& (lex->supatok[var->z - 3] == TK_REDIR_E
			|| lex->supatok[var->z - 3] == TK_REDIR_E2)
		&& lex->supatok[var->z - 1] == TK_PIPE)
	{
		close(var->fd);
		var->fd = open("tmp/tmp.txt", O_CREAT
				| O_TRUNC | O_RDONLY, 0777);
		dup2(var->fd, STDIN_FILENO);
	}
	else if (var->z > 0 && (var->last_pipe == 1
			|| lex->supatok[var->z - 1] == TK_PIPE))
		dup2(var->fd, STDIN_FILENO);
	executeur_final(lex->s[var->z], g_global.cpyenv, var, lex);
}

int	pro(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (lex->s[var->z + 1] == NULL)
	{
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
		{
			child_pro(lex, var);
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
