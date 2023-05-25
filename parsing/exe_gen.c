/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:42:04 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/25 21:26:03 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	parent_pro2(t_var *var, t_pipe *pip)
{
	if (var->fd != 0 && var->last_pipe != 1)
		close(var->fd);
	var->pidnum++;
	wait_pid(var, pip);
	g_global.is_in_cat = 0;
	if (g_global.exitcode == 130)
	{
		var->last_err_com = 130;
	}
	if (g_global.lacontedetagrandmere > 0)
	{
		var->last_err_com = 130;
		g_global.lacontedetagrandmere = 0;
	}
}

void	parent_pro(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (var->fd != 0 && var->last_pipe != 1)
		close(var->fd);
	wait_pid(var, pip);
	parent_pro2(var, pip);
	if (g_global.exitcode == 0)
	{
		var->last_err_com = WEXITSTATUS(pip->status);
		if (WIFSIGNALED(pip->status))
			var->last_err_com = WTERMSIG(pip->status);
		if (var->last_err_com == 11)
			(norm(), printf("Segmentation fault (core dumped)\n"),
				var->last_err_com += 128);
		if (var->last_err_com == 10)
			(norm(), printf("Bus error\n"), var->last_err_com += 128);
		if (var->last_err_com == 2 && g_global.bowlingboolean == 0)
			var->last_err_com += 128;
		if (var->last_err_com == 243)
			var->last_err_com -= 241;
	}
	free_final(lex, pip, var);
	var->last_pipe = 0;
}

void	exe_s3(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (lex->supatok[var->z] == TK_BOUT)
		var->z++;
	else if (lex->supatok[var->z] == TK_PIPE)
	{
		if (lex->s[var->z + 1] == NULL)
		{
			var->last_pipe = 1;
		}
		var->fail_dir = 0;
		minipipe(pip, lex, var);
	}
	else if (lex->supatok[var->z] == TK_REDIR_S
		|| lex->supatok[var->z] == TK_REDIR_E
		|| lex->supatok[var->z] == TK_REDIR_S2
		|| lex->supatok[var->z] == TK_REDIR_E2)
	{
		miniredir_s(lex, var, pip);
		var->i = 0;
	}
	else
		var->z++;
}

void	exe_s2(t_lex *lex, t_var *var, t_pipe *pip)
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
	else if (lex->supatok[var->z] == TK_BOUT
		&& lex->s[var->z + 1] == NULL)
	{
		exec_builtin_out(lex->s[var->z], var, lex, pip);
		var->z++;
	}
	else
		exe_s3(lex, var, pip);
}

int	exe_s(t_lex *lex, t_var *var, t_pipe *pip)
{
	var->fd = dup(0);
	var->z = 0;
	var->i = 0;
	if (lex->s[var->z] == NULL)
	{
		free_final(lex, pip, var);
		return (0);
	}
	var->memo = 0;
	while (var->z < ft_malloc(lex) - 1)
	{
		if (lex->supatok[var->z] == TK_WORD && lex->s[var->z] != NULL)
		{
			if (pro(lex, var, pip) == 0)
				return (0);
		}
		else
			exe_s2(lex, var, pip);
	}
	free_final(lex, pip, var);
	return (0);
}
