/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:22:17 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/27 15:00:39 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	executeur_final22(char *cmdpath, char **s, char **env)
{
	if (cmdpath != NULL && cmdpath[0] == '1')
	{
		free(cmdpath);
		(n(), printf("bash: %s: Permission denied\n", s[0]),
			g_global.exitcode = 126);
		exit(g_global.exitcode);
	}
	if (cmdpath != NULL && cmdpath[0] == '2')
	{
		free(cmdpath);
		(n(), printf("bash: %s: is a directory\n", s[0]),
			g_global.exitcode = 126);
		exit(g_global.exitcode);
	}
	g_global.exitcode = 0;
	execve(cmdpath, s, env);
}

void	executeur22(char **s, char **env, char *cmdpath)
{
	if (cmdpath != NULL && cmdpath[0] == '1')
	{
		printf("bash: %s: Permission denied\n", s[0]);
		g_global.exitcode = 126;
		exit(g_global.exitcode);
	}
	if (cmdpath != NULL && cmdpath[0] == '2')
	{
		printf("bash: %s: is a directory\n", s[0]);
		g_global.exitcode = 126;
		exit(g_global.exitcode);
	}
	if (cmdpath == NULL)
	{
		if (s[0][1] == '.' && s[0][1] == '.' && s[0][2] == '/')
			printf("minishell: no such file or directory: %s\n", s[0]);
		else
		{
			printf("bash : %s: command not found\n", s[0]);
			g_global.exitcode = 127;
		}
		exit(g_global.exitcode);
	}
	execve(cmdpath, s, env);
}

void	executeur(char **s, char **env, t_var *var)
{
	char	*cmdpath;

	cmdpath = find_cmd_path(var, s[0]);
	if (var->nopath == 0)
		cmdpath = 0;
	if (var->last_pipe == 1)
	{
		dup2(var->fd, STDIN_FILENO);
	}
	executeur22(s, env, cmdpath);
}
