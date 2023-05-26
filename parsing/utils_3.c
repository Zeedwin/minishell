/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:37:26 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/26 10:30:13 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	**add_after_redir(char **s1, char **s2)
{
	int		i;
	int		j;
	char	**s3;

	i = 0;
	j = 1;
	s3 = malloc(sizeof(char *) * (ft_strstrlen(s1) + ft_strstrlen(s2)));
	while (s1[i] != NULL)
	{
		s3[i] = malloc(sizeof(char) * (ft_strlen(s1[i]) + 1));
		s3[i] = ft_strcpy(s3[i], s1[i]);
		i++;
	}
	while (s2[j] != NULL)
	{
		s3[i] = malloc(sizeof(char) * (ft_strlen(s2[j]) + 1));
		s3[i] = ft_strcpy(s3[i], s2[j]);
		i++;
		j++;
	}
	free_2(s1);
	s3[i] = NULL;
	return (s3);
}

char	**add_if_after(char **s1)
{
	int		i;
	int		j;
	char	**s2;

	i = 0;
	j = 1;
	printf("s1 = %p\n", s1);
	fflush(stdout);
	s2 = malloc(sizeof(char *) * (ft_strstrlen(s1) + 1));
	while (s1[j] != NULL)
	{
		s2[i] = malloc(sizeof(char) * (ft_strlen(s1[j]) + 1));
		s2[i] = ft_strcpy(s2[i], s1[j]);
		i++;
		j++;
	}
	s2[i] = NULL;
	return (s2);
}

int	miniredir_s1(t_lex *lex, t_var *var)
{
	if ((lex->supatok[var->z + var->i] == TK_REDIR_S
			|| lex->supatok[var->z + var->i] == TK_REDIR_S2
			|| lex->supatok[var->z + var->i] == TK_REDIR_E
			|| lex->supatok[var->z + var->i] == TK_REDIR_E2)
		&& (var->z == 0 || lex->supatok[var->z - 1] == TK_PIPE)
		&& lex->s[var->z + 1][1] != NULL)
	{
		lex->s = cpytrichar(lex->s, var->z);
		lex->s[var->z][0] = ft_strdup(lex->s[var->z + 2][1]);
		var->check_after_redir = 1;
		turbotokenizer2(lex);
		return (1);
	}
	return (0);
}

int	miniredir_s3(t_lex *lex, t_var *var)
{
	if (lex->supatok[var->z + var->i] == TK_REDIR_S)
	{
		if (var->fd_s != -2)
			close(var->fd_s);
		var->fd_s = open(lex->s[var->z + var->i + 1][0],
				O_CREAT | O_WRONLY | O_TRUNC, 0777);
		var->memo = var->z + var->i + 1;
	}
	else if (lex->supatok[var->z + var->i] == TK_REDIR_E)
	{
		if (var->fd_e != -2)
			close(var->fd_e);
		var->fd_e = open(lex->s[var->z + var->i + 1][0], O_RDWR, 0777);
		if (var->fd_e == -1 && errno == ENOENT)
		{
			if (var->fail_dir == 0)
				printf("minishell: no such file or directory: %s\n",
					lex->s[var->z + var->i + 1][0]);
			var->fail_dir = 1;
			return (0);
		}
	}
	return (1);
}

int	miniredir_s(t_lex *lex, t_var *var, t_pipe *pip)
{
	int	plus;
	int	fdtmp;

	plus = miniredir_s1(lex, var);
	var->z += plus;
	var->did_fail = 0;
	var->fd_e = -2;
	var->i = 0;
	fdtmp = dup(0);
	if (var->z > 2 && lex->supatok[var->z - 3] != TK_BOUT)
	{
		close(var->fd);
		var->fd = open("tmp/tmp.txt", O_CREAT | O_TRUNC | O_RDONLY, 0777);
	}
	dup2(STDOUT_FILENO, fdtmp);
	var->fd_s = -2;
	while (lex->supatok[var->z + var->i] == TK_REDIR_S
		|| lex->supatok[var->z + var->i] == TK_REDIR_E
		|| lex->supatok[var->z + var->i] == TK_REDIR_S2
		|| lex->supatok[var->z + var->i] == TK_REDIR_E2)
	{
		if (miniredir_s3(lex, var) == 0)
			break ;
		else if (miniredir_s4(lex, var) == -1)
			break ;
	}
	if (miniredir_s8(lex, var, fdtmp, pip) == 0)
		return (1);
	miniredir_s7(lex, var, pip);
	return (1);
}
