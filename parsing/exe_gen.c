/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe_gen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 16:42:04 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/18 14:52:59 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	exe_s(t_lex *lex, t_var *var, t_pipe *pip)
{	
	if (var->c == 0)
	{	
		var->c++;
		var->z = 0;
	}
	var->i = 0;
	if (lex->s[var->z] == NULL)
	{
		free_final(lex, pip, var);
		return (0);
	}
	var->memo = 0;
	var->fd = dup(0);
	while (var->z < ft_malloc(lex) - 1)
	{
		if (lex->supatok[var->z] == TK_WORD && lex->s[var->z] != NULL)
		{
			if (lex->s[var->z + 1] == NULL)
			{
				g_global.is_in_cat = 1;
				var->shell[var->pidnum] = fork();
				if (var->shell[var->pidnum] == 0)
				{
					if (var->z > 0 && var->last_pipe == 1)
					{
						dup2(var->fd, STDIN_FILENO);
					}
					if (var->z > 0 && lex->supatok[var->z - 1] == TK_PIPE)
					{
						dup2(var->fd, STDIN_FILENO);
					}
					if (var->z >= 2 && lex->supatok[var->z - 2] == TK_REDIR_S)
					{
						var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
						dup2(var->fd, STDIN_FILENO);
					}
					if ((var->z > 1 && lex->supatok[var->z - 1 - var->check_after_redir] == TK_PIPE
							&& (lex->supatok[var->z - 3 - var->check_after_redir] == TK_REDIR_E2
								|| lex->supatok[var->z - 3 - var->check_after_redir] == TK_REDIR_E)))
					{
						var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
						dup2(var->fd, STDIN_FILENO);
					}
					else if ((var->z > 1 && lex->supatok[var->z - 1 - var->check_after_redir] == TK_PIPE)
						|| (var->z > 2 && lex->supatok[var->z - 3] == TK_REDIR_S && lex->supatok[var->z - 1] == TK_PIPE))
					{
						var->fd = open(lex->s[var->memo][0], O_RDWR, 0777);
						dup2(var->fd, STDIN_FILENO);
					}
					executeur_final(lex->s[var->z], g_global.cpyenv, var, lex);
				}
				else
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
					free_final(lex, pip, var);
					var->last_pipe = 0;
					return (0);
				}
			}
			else
				var->z++;
		}
		else if (lex->supatok[var->z] == TK_BUILTIN
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
			var->z++;
		}
		else if (lex->supatok[var->z] == TK_BUILTIN_OUTP)
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
			var->c = 0;
			var->i = 0;
		}
		else
			var->z++;
	}
	free_final(lex, pip, var);
	return (0);
}
