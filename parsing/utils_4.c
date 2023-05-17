/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:00:20 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/17 16:50:35 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	miniredir_s4(t_lex *lex, t_var *var)
{
	if (lex->supatok[var->z + var->i] == TK_REDIR_S2)
	{
		if (var->fd_s != -2)
			close (var->fd_s);
		var->fd_s = open(lex->s[var->z + var->i + 1][0],
				O_CREAT | O_APPEND | O_WRONLY, 0777);
		var->memo = var->z + var->i + 1;
	}
	else if (lex->supatok[var->z + var->i] == TK_REDIR_E2)
	{
		var->did_fail |= delimiteur(lex, var);
		if (var->fd_e != -2)
			close (var->fd_e);
		var->fd_e = open("tmp/tmp.txt", O_RDWR, 0777);
	}
	if (var->z > 0 && var->check_after_redir == 0)
		lex->s[var->z - 1] = add_after_redir(
				lex->s[var->z - 1],
				lex->s[var->z + var->i + 1]);
	if (var->z > 0 && var->check_after_redir == 1 && var->i > 0)
		lex->s[var->z - 1] = add_after_redir(
				lex->s[var->z - 1],
				lex->s[var->z + var->i + 1]);
	var->i = var->i + 2;
	return (var->did_fail);
}

void	miniredir_s5(t_lex	*lex, t_var *var)
{
	if (var->last_pipe == 1)
		dup2(var->fd, STDIN_FILENO);
	if (var->z > 1 && lex->supatok[var->z - 2] == TK_PIPE)
		dup2(var->fd, STDIN_FILENO);
	if (var->z > 2 && lex->supatok[var->z - 2] == TK_PIPE
		&& lex->supatok[var->z - 3] == TK_BUILTIN_OUTP)
	{
		var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
		dup2(var->fd, STDIN_FILENO);
	}
	if (var->fd_e != -2)
		dup2(var->fd_e, STDIN_FILENO);
	if (var->fd_s != -2 && find_cmd_path(var,
			lex->s[var->z - 1][0]) != 0)
		dup2(var->fd_s, STDOUT_FILENO);
	executeur(lex->s[var->z - 1], g_global.cpyenv, var);
}

void	miniredir_s6(t_lex *lex, t_var *var, t_pipe *pip)
{
	var->pidnum++;
	if (var->z + 1 + var->i >= ft_malloc(lex) - 2)
	{
		if (var->fd != 0)
			close(var->fd);
		wait_pid(var, pip);
	}
	g_global.is_in_cat = 0;
	var->z = var->z + 1 + var->i;
	var->last_pipe = 0;
}

int	miniredir_s8(t_lex *lex, t_var *var, int fdtmp)
{
	if (var->z > 0 && var->fail_dir == 0
		&& lex->supatok[var->z - 1] == TK_BUILTIN_OUTP)
	{
		if (var->fd_s != -2 && find_cmd_path(var,
				lex->s[var->z - 1][0]) != 0)
			dup2(var->fd_s, STDOUT_FILENO);
		exec_builtin_out(lex->s[var->z - 1], var, lex);
		dup2(fdtmp, STDOUT_FILENO);
		var->z = var->z + 1 + var->i;
		return (0);
	}
	return (1);
}

int	miniredir_s7(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (var->fail_dir == 0 && var->z  > 0 && var->did_fail == 0)
	{	
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
			miniredir_s5(lex, var);
		else
			miniredir_s6(lex, var, pip);
		return (0);
	}
	else if (var->fail_dir == 0 && var->z > 1
		&& lex->supatok[var->z - 2] == TK_BUILTIN_OUTP)
	{
		var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
		dup2(var->fd, STDIN_FILENO);
		return (0);
	}
	else
		var->z = var->z + 1 + var->i;
	return (1);
}
