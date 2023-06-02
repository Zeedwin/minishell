/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_gen2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 12:51:32 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 13:15:44 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	fd_redir(t_var	*var)
{
	close(var->fd);
	var->fd = open("tmp/tmp.txt", O_CREAT
			| O_TRUNC | O_RDONLY, 0777);
	dup2(var->fd, STDIN_FILENO);
}

void	fd_reinit(t_var	*var)
{
	close(var->fd);
	var->fd = open("tmp/tmp.txt", O_RDONLY, 0777);
}

void	child_pro(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (var->z > 2 && (lex->supatok[var->z - 3] == TK_REDIR_S
			|| lex->supatok[var->z - 3] == TK_REDIR_S2)
		&& lex->supatok[var->z - 1] == TK_PIPE)
		fd_redir(var);
	else if (((var->z > 3 && lex->supatok[var->z - 4] == TK_PIPE)
			|| var->z - 3 == 0)
		&& (lex->supatok[var->z - 3] == TK_REDIR_E
			|| lex->supatok[var->z - 3] == TK_REDIR_E2)
		&& lex->supatok[var->z - 1] == TK_PIPE
		&& lex->supatok[var->z - 4] != TK_BOUT)
		fd_redir(var);
	else if (var->z > 0 && (var->last_pipe == 1
			|| lex->supatok[var->z - 1] == TK_PIPE))
	{
		if (var->z > 3 && (lex->supatok[var->z - 3] == TK_REDIR_E
				|| lex->supatok[var->z - 3] == TK_REDIR_E2)
			&& lex->supatok[var->z - 4] == TK_BOUT)
			fd_reinit(var);
		dup2(var->fd, STDIN_FILENO);
	}
	execute_final(lex->s[var->z], var, lex, pip);
}

int	pro(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (lex->s[var->z + 1] == NULL)
	{
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
		{
			child_pro(lex, var, pip);
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

void	exe_gen_test(t_lex *lex, t_var *var)
{
	if (lex->s[var->z] == NULL)
		var->z++;
	else if (check_slash2(lex->s[var->z][0]) == 0)
		(n(), printf("bash: %s : command not found\n",
				lex->s[var->z][0]), var->z++);
}
