/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:00:20 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 20:32:51 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	miniredir_s5(t_lex	*lex, t_var *var, t_pipe *pip)
{
	if (var->z > 2 && lex->supatok[var->z - 2] == TK_PIPE
		&& lex->supatok[var->z - 3] == TK_WORD)
		dup2(var->fd, STDIN_FILENO);
	if (var->z > 2 && lex->supatok[var->z - 2] == TK_PIPE
		&& lex->supatok[var->z - 3] == TK_BOUT)
		microredir(var);
	if (var->z > 4 && (lex->supatok[var->z - 4] == TK_REDIR_E
			|| lex->supatok[var->z - 4] == TK_REDIR_E2)
		&& lex->supatok[var->z - 5] == TK_BOUT)
		microredir(var);
	if (var->fd_e != -2)
		dup2(var->fd_e, STDIN_FILENO);
	if (var->fd_s != -2 && find_cmd_path(var,
			lex->s[var->z - 1][0]) != 0)
		dup2(var->fd_s, STDOUT_FILENO);
	if (find_cmd_path(var, lex->s[var->z - 1][0]) != 0
		&& lex->supatok[var->z + 2] == TK_PIPE
		&& (lex->supatok[var->z] == TK_REDIR_E
		|| lex->supatok[var->z] == TK_REDIR_E2))
		dup2(pip->tube[1], STDOUT_FILENO);
	close(pip->tube[0]);
	execute(lex->s[var->z - 1], g_global.cpyenv, var);
}

void	miniredir_s6(t_lex *lex, t_var *var, t_pipe *pip)
{
	char	*s;

	s = find_cmd_path(var, lex->s[var->z - 1][0]);
	if (s != 0 && lex->supatok[var->z + 2] == TK_PIPE)
	{
		close(var->fd);
		var->fd = pip->tube[0];
	}
	close(pip->tube[1]);
	if (var->fd_s != -2)
		close (var->fd_s);
	if (var->fd_e != -2)
		close (var->fd_e);
	var->z = var->z + 1 + var->i;
	if (lex->s[var->z - 1] == NULL)
	{
		close(var->fd);
		wait_pid(var, pip);
	}
	var->pidnum++;
	g_global.is_in_cat = 0;
	var->last_pipe = 0;
	free(s);
}

int	miniredir_s8(t_lex *lex, t_var *var, int fdtmp, t_pipe *pip)
{
	if (var->z > 0 && var->fail_dir == 0
		&& lex->supatok[var->z - 1] == TK_BOUT)
	{
		if (lex->supatok[var->z + 2] == TK_PIPE)
		{
			close(var->fd);
			var->fd = open("/tmp/tmp.txt", O_CREAT | O_TRUNC | O_RDWR, 0777);
			dup2(var->fd, STDOUT_FILENO);
		}
		if (var->fd_s != -2 && find_cmd_path(var,
				lex->s[var->z - 1][0]) != 0)
			dup2(var->fd_s, STDOUT_FILENO);
		exec_builtin_out(lex->s[var->z - 1], var, lex, pip);
		dup2(fdtmp, STDOUT_FILENO);
		var->z = var->z + 1 + var->i;
		if (lex->s[var->z - 1] == NULL)
		{
			close(var->fd);
			wait_pid(var, pip);
		}
		return (0);
	}
	return (1);
}

int	miniredir_s7(t_lex *lex, t_var *var, t_pipe *pip)
{
	if (var->fail_dir == 0 && var->z > 0 && var->did_fail == 0
		&& lex->supatok[var->z - 1] != TK_PIPE
		&& check_empty(lex->s[var->z - 1][0]) != 0)
	{
		g_global.is_in_cat = 1;
		pipe(pip->tube);
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
			miniredir_s5(lex, var, pip);
		else
			miniredir_s6(lex, var, pip);
		return (0);
	}
	else if (var->fail_dir == 0 && var->z > 1
		&& lex->supatok[var->z - 2] == TK_BOUT
		&& lex->supatok[var->z - 1] != TK_NULL)
	{		
		var->fd = open("/tmp/tmp.txt", O_RDWR, 0777);
		dup2(var->fd, STDIN_FILENO);
		return (0);
	}
	else
		var->z = var->z + 1 + var->i;
	return (1);
}

int	ini_i(char *s, int i)
{
	i++;
	while (s[i] != '\0' && s[i] != '\'')
			i++;
	i++;
	return (i);
}
