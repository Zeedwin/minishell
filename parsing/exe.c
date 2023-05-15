/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 09:55:04 by hdelmann          #+#    #+#             */
/*   Updated: 2023/04/27 09:55:04 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	exec_builtin_out(char **s, t_var *var, t_lex *lex)
{
	if (ft_strcmp(*s, "pwd") == 0 || ft_strcmp(*s, "PWD") == 0)
		pwd();
	else if (ft_strcmp(*s, "env") == 0 || ft_strcmp(*s, "ENV") == 0)
		env(g_global.cpyenv);
	else if (ft_strcmp(*s, "echo") == 0)
		echo(var, lex);
	else if (ft_strcmp(lex->s[var->z][0], "exit") == 0)
		ft_exit(var, lex);
	return (1);
}

int	execve_builtin(char **s, char **env, t_var *var, t_lex *lex)
{
	(void)env;
	int i;

	i = 1;
	if (ft_strcmp(*s, "cd") == 0 || ft_strcmp(*s, "CD") == 0)
		cd(s, var);
	if (ft_strcmp(*s, "export") == 0)
		g_global.cpyenv = export(g_global.cpyenv, lex, var);
	if (ft_strcmp(*s, "unset") == 0)
	{
		while (lex->s[var->z][i])
		{
			g_global.cpyenv = unset(g_global.cpyenv, lex->s[var->z][i]);
			i++;
		}
	}
	return (0);
}

char	*check_doc(char *s)
{
	int		j;
	int		i;
	char	*s1;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	s1 = malloc(sizeof(char) * (i - 1));
	i = 0;
	j = 2;
	while (s[j] != '\0')
	{
		s1[i] = s[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	i = open(s1, O_RDWR, 0777);
	if (i == -1 && errno == ENOENT)
		return (0);
	close(i);
	return (s1);
}

char	*check_replace_prog(char *s, t_var *var)
{
	char	*s1;
	int		i;
	int		j;

	i = ft_strlen(var->line) + ft_strlen(s);
	j = 0;
	s1 = NULL;
	if (s[0] == '.')
	{
		if (s[1] == '/')
		{
			if (check_doc(s) != 0)
			{
				s = check_doc(s);
				s1 = malloc(sizeof(char) * i);
				i = 0;
				while (var->line[i] != '\0')
				{
					s1[i] = var->line[i];
					i++;
				}
				s1[i] = '/';
				i++;
				while (s[j] != '\0')
				{
					s1[i] = s[j];
					i++;
					j++;
				}
				s1[i] = '\0';
			}
			else
			{
				return (0);
			}
		}
	}
	return (s);
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
	if (cmdpath == 0)
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
			//g_global.lacontedetagrandmere = 0;
		}
		exit(g_global.exitcode);
	}
	//s[0] = remo_slash(s[0]);
	g_global.exitcode = 0;
	execve(cmdpath, s, env);
}
