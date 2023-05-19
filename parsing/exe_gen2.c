/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_gen2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 15:52:29 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/19 16:15:31 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	last_comd(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (lex->s[var->z + 1] == NULL)
	{
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
			child_l_cmd(lex, var);
		else
			return (last_cmd(lex, var, pip), 0);
	}
	else
		var->z++;
	return (0);
}

void	exe_gen3(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (lex->supatok[var->z] == TK_BUILTIN_OUTP)
		var->z++;
	else if (lex->supatok[var->z] == TK_PIPE)
	{
		if (lex->s[var->z + 1] == NULL)
			var->last_pipe = 1;
		var->fail_dir = 0;
		minipipe(pip, lex, var);
	}
	else if (lex->supatok[var->z] == TK_REDIR_S
		|| lex->supatok[var->z] == TK_REDIR_E
		|| lex->supatok[var->z] == TK_REDIR_S2
		|| lex->supatok[var->z] == TK_REDIR_E2)
	{
		miniredir_s(lex, var, pip);
		var->c = 0;
		var->i = 0;
	}
	else
		var->z++;
}

void	exe_gen2(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (lex->supatok[var->z] == TK_BUILTIN
		&& lex->supatok[var->z + 1] == TK_PIPE)
		var->z += 2;
	else if (var->z > 0 && lex->supatok[var->z] == TK_BUILTIN
		&& lex->supatok[var->z - 1] == TK_PIPE)
		var->z++;
	else if (lex->supatok[var->z] == TK_BUILTIN && var->z == 0)
	{
		execve_builtin(lex->s[var->z], var, lex);
		var->z++;
	}
	else if (lex->supatok[var->z] == TK_BUILTIN_OUTP
		&& lex->s[var->z + 1] == NULL)
	{
		exec_builtin_out(lex->s[var->z], var, lex);
		printf("oo111");
		close(var->fd);
		close(var->fd_s);
		close(var->fd_e);
		wait_pid(var, pip);
		var->z++;
	}
	else
		exe_gen3(lex, var, pip);
}
