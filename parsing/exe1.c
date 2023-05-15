/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:47:01 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/15 13:48:12 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	executeur_final(char **s, char **env, t_var *var, t_lex *lex)
{
	char	*cmdpath;

	if (var->last_pipe == 1)
		dup2(var->fd, STDIN_FILENO);
	if (var->z > 0 && lex->supatok[var->z - 1] == TOKEN_PIPE)
		dup2(var->fd, STDIN_FILENO);
	if (var->z >= 2 && lex->supatok[var->z - 1] == TOKEN_PIPE
		&& lex->supatok[var->z - 2] == TOKEN_BUILTIN_OUTP)
	{
		var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
		dup2(var->fd, STDIN_FILENO);
	}
	cmdpath = find_cmd_path(var, s[0]);
	if (var->nopath == 0)
		cmdpath = 0;
	if (cmdpath == 0)
	{
		if (g_global.lacontedetagrandmere > 0)
			g_global.exitcode = 130;
		if (s[0][1] == '.' && s[0][1] == '.' && s[0][2] == '/')
			printf("minishell: no such file or directory: %s\n", s[0]);
		else if (var->fail_dir == 0)
		{
			printf("bash : %s: command not found\n", s[0]);
			g_global.exitcode = 127;
		}
		else if (g_global.exitcode == 130 && var->fail_dir == 0)
		{
			printf("bash : %d: command not found\n", g_global.last_err_com);
		}
		exit(g_global.exitcode);
	}
	g_global.exitcode = 0;
	execve(cmdpath, s, env);
}
