/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:47:01 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/27 13:56:39 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	executeur_final2(char **s, t_var *var)
{
	if (g_global.lacontedetagrandmere > 0)
		g_global.exitcode = 130;
	if (s[0][1] == '.' && (s[0][1] == '.' && s[0][2] == '/'))
		printf("minishell: no such file or directory: %s\n", s[0]);
	else if (var->fail_dir == 0)
	{
		printf("bash : %s: command not found\n", s[0]);
		g_global.exitcode = 127;
	}
	else if (g_global.exitcode == 130 && var->fail_dir == 0)
		printf("bash : %d: command not found\n", g_global.last_err_com);
	close(var->fd);
	exit(g_global.exitcode);
}

void	executeur_final(char **s, char **env, t_var *var, t_lex *lex)
{
	char	*cmdpath;

	if (var->last_pipe == 1)
		dup2(var->fd, STDIN_FILENO);
	if (var->z > 0 && lex->supatok[var->z - 1] == TK_PIPE)
		dup2(var->fd, STDIN_FILENO);
	if (var->z >= 2 && lex->supatok[var->z - 1] == TK_PIPE
		&& lex->supatok[var->z - 2] == TK_BOUT)
	{
		(n(), close(var->fd), var->fd = open("tmp/tmp.txt", O_RDWR, 0777));
		dup2(var->fd, STDIN_FILENO);
	}
	cmdpath = find_cmd_path(var, s[0]);
	if (var->nopath == 0)
		cmdpath = 0;
	if (cmdpath == 0)
	{
		executeur_final2(s, var);
		return ;
	}
	else
		executeur_final22(cmdpath, s, env);
}

void	init_sign(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlbs);
}
