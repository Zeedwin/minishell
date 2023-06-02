/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:47:01 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 13:22:20 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	execute_final2(char **s, t_var *var, t_lex *lex, t_pipe *pip)
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
	free_final(lex, pip, var);
	exit(g_global.exitcode);
}

void	execute_final(char **s, t_var *var, t_lex *lex, t_pipe *pip)
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
		execute_final2(s, var, lex, pip);
		return ;
	}
	else
		execute_final22(cmdpath, s, var->cpyenv);
}

int	check_eq2(char *str, t_var *var)
{
	int	i;

	i = 0;
	if (str[0] == '$')
		return (exportprint(var->cpyenv, var), 1);
	while (str[i])
	{
		if (isalpha(str[i]) == 0 && !str[i + 1])
		{
			printf("bash: export: `%c': not a valid identifier\n", str[i]);
			g_global.last_err_com = 1;
			return (1);
		}
		i++;
	}
	return (0);
}

void	init_sign(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlbs);
}
