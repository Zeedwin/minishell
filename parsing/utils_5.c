/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 13:38:19 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/16 14:50:36 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	delimiteur2(t_lex *lex, char *buffer, int plus, t_var *var)
{
	ssize_t	num_read;
	char	*s;

	s = NULL;
	num_read = 0;
	var->is_in_heredoc = 2;
	g_global.lacontedetagrandmere += 1;
	var->fd_hdoc = open("tmp/tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
		num_read = read(STDIN_FILENO, buffer, BUF_SIZE);
		buffer[num_read] = '\0';
		s = del_backn(buffer);
		if (ft_strcmp(s, lex->s[var->z + var->i + plus + 1][0]) == 0)
		{
			close(var->fd_hdoc);
			exit(0);
		}
		write(var->fd_hdoc, buffer, num_read);
	}
}

void	minipipe1(t_var *var, t_pipe *pip, t_lex *lex)
{
	dup2(var->fd, STDIN_FILENO);
	if (find_cmd_path(var, lex->s[var->z - 1][0]) != 0
		&& lex->supatok[var->z - 1] == TK_WORD)
		dup2(pip->tube[1], STDOUT_FILENO);
	close(pip->tube[0]);
	if (lex->supatok[var->z - 1] == TK_WORD)
	{
		executeur(lex->s[var->z - 1], g_global.cpyenv, var);
	}
	exit (0);
}

void	minipipe2(t_var *var, t_pipe *pip)
{
	if (var->fd != 0 && var->last_pipe != 1)
		close(var->fd);
	var->pidnum++;
	g_global.is_in_cat = 0;
	close(pip->tube[1]);
	var->fd = pip->tube[0];
	var->z += 1;
}

void	minipipe3(t_var *var, t_lex *lex, int fdtmp)
{
	var->fd = open("tmp/tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	dup2(var->fd, STDOUT_FILENO);
	close(var->fd);
	exec_builtin_out(lex->s[var->z - 1], var, lex);
	dup2(fdtmp, STDOUT_FILENO);
	var->z++;
}

int	turbotokenizer1(t_lex *lex, int i)
{
	if (lex->s[i][0][0] == '>' && lex->s[i][0][0 + 1] != '>')
		lex->supatok[i] = TK_REDIR_S;
	else if (lex->s[i][0][0] == '<' && lex->s[i][0][0 + 1] != '<')
		lex->supatok[i] = TK_REDIR_E;
	else if (lex->s[i][0][0] == '>' && lex->s[i][0][0 + 1] == '>')
		lex->supatok[i] = TK_REDIR_S2;
	else if (lex->s[i][0][0] == '<' && lex->s[i][0][0 + 1] == '<')
		lex->supatok[i] = TK_REDIR_E2;
	return (0);
}
