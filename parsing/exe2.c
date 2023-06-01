/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:22:17 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/01 16:09:59 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	execute_final22(char *cmdpath, char **s, char **env)
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

void	execute22(char **s, char **env, char *cmdpath)
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

void	execute(char **s, char **env, t_var *var)
{
	char	*cmdpath;

	cmdpath = find_cmd_path(var, s[0]);
	if (var->nopath == 0)
		cmdpath = 0;
	if (var->last_pipe == 1)
	{
		dup2(var->fd, STDIN_FILENO);
	}
	execute22(s, env, cmdpath);
}

void	execve_un(t_var *var, t_lex *lex)
{
	int		i;
	void	*a;

	i = 0;
	while (lex->s[var->z][i] && lex->s[var->z][i] != NULL)
		(n(), a = g_global.cpyenv, g_global.cpyenv
			= unset(g_global.cpyenv, lex->s[var->z][i]), i++, free(a));
}
