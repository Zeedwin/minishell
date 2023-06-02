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
	{
		pwd();
		var->last_err_com = 0;
	}
	else if (ft_strcmp(*s, "env") == 0 || ft_strcmp(*s, "ENV") == 0)
		env(var->cpyenv);
	else if (ft_strcmp(*s, "echo") == 0)
		echo(var, lex);
	else if (ft_strcmp(lex->s[var->z][0], "exit") == 0)
		ft_exit(var, lex, pip, 0);
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
		{
			printf("bash: export: `=': not a valid identifier\n");
			g_global.last_err_com = 1;
		}
		i++;
	}
}

void	execve_builtin(char **s, t_var *var, t_lex *lex)
{
	t_ini	p;
	char	**envtmp;

	if (ft_strcmp(*s, "cd") == 0 || ft_strcmp(*s, "CD") == 0)
		cd(s, var);
	p.i = 1;
	if (ft_strcmp(*s, "export") == 0)
	{
		if (!lex->s[var->z][1])
			exportprint(var->cpyenv, var);
		else
		{
			while (lex->s[var->z] && lex->s[var->z][p.i]
				&& check_empty(lex->s[var->z][p.i]))
			{
				if (check_eq2(lex->s[var->z][p.i], var) == 0)
				{
					envtmp = export2(var->cpyenv, lex, var, p.i);
					free_2(var->cpyenv);
					var->cpyenv = ft_strcpy_env(var->cpyenv, envtmp);
					free_2(envtmp);
				}
				p.i++;
			}
		}
	}
	p.i = 1;
	if (ft_strcmp(*s, "unset") == 0)
		execve_un(var, lex);
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
