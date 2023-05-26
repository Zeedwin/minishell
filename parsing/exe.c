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

int	exec_builtin_out(char **s, t_var *var, t_lex *lex, t_pipe *pip)
{
	if (ft_strcmp(*s, "pwd") == 0 || ft_strcmp(*s, "PWD") == 0)
		pwd();
	else if (ft_strcmp(*s, "env") == 0 || ft_strcmp(*s, "ENV") == 0)
		env(g_global.cpyenv);
	else if (ft_strcmp(*s, "echo") == 0)
		echo(var, lex);
	else if (ft_strcmp(lex->s[var->z][0], "exit") == 0)
		ft_exit(var, lex);
	if (lex->s[var->z + 1] == NULL)
	{
		close(var->fd);
		wait_pid(var, pip);
	}
	return (1);
}

void	check_eq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!str[i - 1] && str[i] == '=' && !str[i + 1])
			printf("bash: export: `=': not a valid identifier\n");
		i++;
	}
}

int	execve_builtin(char **s, t_var *var, t_lex *lex)
{
	int	i;

	if (ft_strcmp(*s, "cd") == 0 || ft_strcmp(*s, "CD") == 0)
		cd(s, var);
	i = 1;
	if (ft_strcmp(*s, "export") == 0)
	{
		if (lex->s[var->z][1] == NULL)
			g_global.cpyenv = export(g_global.cpyenv, lex, var, 0);
		else
		{
			while (lex->s[var->z][i] && check_vide(lex->s[var->z][i]))
			{
				check_eq(lex->s[var->z][i]);
				(n(), g_global.cpyenv
					= export(g_global.cpyenv, lex, var, i), i++);
			}
		}
	}
	i = 1;
	if (ft_strcmp(*s, "unset") == 0)
	{
		while (lex->s[var->z][i])
			(n(), g_global.cpyenv
				= unset(g_global.cpyenv, lex->s[var->z][i]), i++);
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

	(n(), i = ft_strlen(var->line) + ft_strlen(s), j = 0, s1 = NULL);
	if (s[0] == '.' && s[1] == '/')
	{
		if (check_doc(s) != 0)
		{
			(n(), s = check_doc(s), s1 = malloc(sizeof(char) * i), i = 0);
			while (var->line[i] != '\0')
			{
				s1[i] = var->line[i];
				i++;
			}
			(n(), s1[i] = '/', i++);
			while (s[j] != '\0')
				(n(), s1[i] = s[j], i++, j++);
			s1[i] = '\0';
		}
		else
			return (0);
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
	if (cmdpath[0] == '1')
	{
		printf("bash: %s: Permission denied\n", s[0]);
		g_global.exitcode = 126;
		exit(g_global.exitcode);
	}
	if (cmdpath[0] == '2')
	{
		printf("bash: %s: is a directory\n", s[0]);
		g_global.exitcode = 126;
		exit(g_global.exitcode);
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
