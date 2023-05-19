/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:42:04 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/19 16:00:39 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	init_exe(t_lex *lex, t_var *var, t_pipe *pip)
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
	var->fd = dup(0);
	return (1);
}

void	last_cmd1(t_var *var, t_pipe *pip)
{
	var->last_err_com = WEXITSTATUS(pip->status);
	if (WIFSIGNALED(pip->status))
		var->last_err_com = WTERMSIG(pip->status);
	if (var->last_err_com == 11)
		(norm(),
			printf("Segmentation fault (core dumped)\n"),
			var->last_err_com += 128);
	if (var->last_err_com == 10)
		(norm(),
			printf("Bus error\n"),
			var->last_err_com += 128);
	if (var->last_err_com == 3)
		var->last_err_com += 128;
}

void	last_cmd(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (var->fd != 0 && var->last_pipe != 1)
		close(var->fd);
	wait_pid(var, pip);
	g_global.is_in_cat = 0;
	if (g_global.exitcode == 130)
		var->last_err_com = 130;
	if (g_global.lacontedetagrandmere > 0)
	{
		var->last_err_com = 130;
		g_global.lacontedetagrandmere = 0;
	}
	else if (g_global.exitcode == 0)
		last_cmd1(var, pip);
	free_final(lex, pip, var);
	var->last_pipe = 0;
}

void	child_l_cmd(t_lex *lex, t_var *var)
{
	if (var->z > 0 && (var->last_pipe == 1
			|| lex->supatok[var->z - 1] == TK_PIPE))
		dup2(var->fd, STDIN_FILENO);
	executeur_final(lex->s[var->z], g_global.cpyenv, var, lex);
}

int	exe_s(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (init_exe(lex, var, pip) == 0)
		return (0);
	while (var->z < ft_malloc(lex) - 1)
	{
		if (lex->supatok[var->z] == TK_WORD && lex->s[var->z] != NULL)
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
		}
		else
			exe_gen2(lex, var, pip);
	}
	free_final(lex, pip, var);
	return (0);
}
