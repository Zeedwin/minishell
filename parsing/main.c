/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:22:43 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/08 02:15:33 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <termios.h>

//#define close(fd) {close(fd);printf("close: %d\n", fd);}
//#define dup2(a,b) {dup2(a,b);printf("%d dup2 : %d,%d\n", __LINE__, a,b);}
t_var	g_global;

char	*ft_realloc(char *map, int i)
{
	char	*map_tp;
	int		x;

	x = 0;
	map_tp = malloc(i * sizeof(char *));
	while (map[x])
	{
		map_tp[x] = map[x];
		x++;
	}
	free(map);
	map_tp[x] = '\0';
	return (map_tp);
}

char	**ft_realloc2(char **map, int i)
{
	char	**map_tp;
	int		x;

	x = 0;
	map_tp = malloc(i * sizeof(char *));
	while (map[x])
	{
		map_tp[x] = ft_strcpy(map_tp[x], map[x]);
		x++;
	}
	free(map);
	map_tp[x] = NULL;
	return (map_tp);
}

int	ft_strstrlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int	check_endcmd(char a)
{
	if (a == '|')
		return (0);
	if (a == '<')
		return (0);
	if (a == '>')
		return (0);
	if (a == '\0')
		return (0);
	return (1);
}

void	init_cmd(t_var *var)
{
	int	i;

	i = 0;
	var->cmd = malloc((ft_strlen(var->line) + 1) * sizeof(char));
	while (check_endcmd(var->line[i]) == 1)
	{
		var->cmd[i] = var->line[i];
		i++;
	}
	var->cmd[i] = '\0';
	var->cmd1 = ft_split(var->cmd, ' ');
}

int	testspace(t_var *var)
{
	int	i;

	i = 0;
	while (var->line[i] != '\0')
	{
		if (var->line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void	historyset(t_var *var, t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	if (var->previous_line == NULL)
		var->previous_line = (var->line);
	if (var->check_pipe == 1)
	{
		while (var->previous_line[i] != '\0')
			i++;
		j = ft_strlen(var->line) + ft_strlen(var->previous_line) + 1;
		var->previous_line = ft_realloc(var->previous_line, j);
		j = 0;
		while (var->line[j] != '\0')
		{
			var->previous_line[i] = var->line[j];
			i++;
			j++;
		}
		var->previous_line[i] = '\0';
		if (lex->supatok[ft_malloc(lex) - 3] != TOKEN_PIPE)
		{
			var->check_pipe = 0;
			add_history(var->previous_line);
		}
	}
	else if (lex->supatok[ft_malloc(lex) - 3] == TOKEN_PIPE)
	{
		var->check_pipe = 1;
	}
	else if (ft_strlen2(var->line) != 0
		&& testspace(var) == 1 && var->check_pipe == 0)
	{
		add_history(var->line);
		var->previous_line = ft_strdup(var->line);
	}
	free(var->previous_line);
}

int	count_pipe(int *supatok, t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex->s[i])
	{
		if (supatok[i] == TOKEN_PIPE)
		{
			j++;
		}
		i++;
	}
	return (j);
}

int	delimiteur(t_lex *lex, t_var *var)
{
	char	buffer[BUF_SIZE];
	char	*s;
	int		fd;
	ssize_t	num_read;
	int		status;
	pid_t	balls;

	var->is_in_heredoc = 1;
	balls = fork();
	if (balls == 0)
	{
		num_read = 0;
		var->is_in_heredoc = 2;
		fd = open("tmp/tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
		while (1)
		{
			num_read = read(STDIN_FILENO, buffer, BUF_SIZE);
			s = del_backn(buffer);
			if (ft_strcmp(s, lex->s[var->z + var->i + 1][0]) == 0)
			{
				close(fd);
				exit(0);
			}
			write(fd, buffer, num_read);
		}
	}
	else
		waitpid(balls, &status, 0);
	var->is_in_heredoc = 0;
	return WEXITSTATUS(status);
}

int	minipipe(t_pipe	*pip, t_lex *lex, t_var *var)
{
	int	fdtmp;

	if (var->c == 0)
	{
		var->c++;
		var->fd = dup(0);
	}
	fdtmp = dup(0);
	dup2(STDOUT_FILENO, fdtmp);
	pipe(pip->tube);
	if (lex->supatok[var->z - 1] != TOKEN_BUILTIN
		&& lex->supatok[var->z - 1] != TOKEN_BUILTIN_OUTP)
	{
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
		{
			dup2(var->fd, STDIN_FILENO);
			if (find_cmd_path(var, lex->s[var->z - 1][0]) != 0
				&& lex->supatok[var->z - 1] == TOKEN_WORD)
				dup2(pip->tube[1], STDOUT_FILENO);
			close(pip->tube[0]);
			if (lex->supatok[var->z - 1] == TOKEN_WORD)
			{
				executeur(lex->s[var->z - 1], g_global.cpyenv, var);
			}
		}
		else
		{
			if (var->fd != 0 && var->last_pipe != 1)
				close(var->fd);
			var->pidnum++;
			g_global.is_in_cat = 0;
			close(pip->tube[1]);
			var->fd = pip->tube[0];
			fflush(stdout);
			var->z += 1;
		}
	}
	else if (lex->supatok[var->z - 1] == TOKEN_BUILTIN_OUTP)
	{
		var->fd = open("tmp/tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
		dup2(var->fd, STDOUT_FILENO);
		close(var->fd);
		exec_builtin_out(lex->s[var->z - 1], var, lex);
		dup2(fdtmp, STDOUT_FILENO);
		var->z++;
	}
	return (1);
}

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
	s3[i] = NULL;
	return (s3);
}

int	miniredir_s(t_lex *lex, t_var *var, t_pipe *pip)
{
	int	fd_e;
	int	fd_s;
	int	fdtmp;
	int	did_fail;

	(void)pip;
	did_fail = 0;
	fd_e = -2;
	fdtmp = dup(0);
	dup2(STDOUT_FILENO, fdtmp);
	fd_s = -2;
	while (lex->supatok[var->z + var->i] == TOKEN_REDIR_S
		|| lex->supatok[var->z + var->i] == TOKEN_REDIR_E
		|| lex->supatok[var->z + var->i] == TOKEN_REDIR_S2
		|| lex->supatok[var->z + var->i] == TOKEN_REDIR_E2)
	{
		if (lex->supatok[var->z + var->i] == TOKEN_REDIR_S)
		{
			close(fd_s);
			fd_s = open(lex->s[var->z + var->i + 1][0],
					O_CREAT | O_WRONLY | O_TRUNC, 0777);
		}
		else if (lex->supatok[var->z + var->i] == TOKEN_REDIR_E)
		{
			close(fd_e);
			fd_e = open(lex->s[var->z + var->i + 1][0], O_RDWR, 0777);
			if (fd_e == -1 && errno == ENOENT)
			{
				printf("minishell: no such file or directory: %s\n",
					lex->s[var->z + var->i + 1][0]);
				break ;
			}
		}
		else if (lex->supatok[var->z + var->i] == TOKEN_REDIR_S2)
		{
			close (fd_s);
			fd_s = open(lex->s[var->z + var->i + 1][0],
					O_CREAT | O_APPEND | O_WRONLY, 0777);
		}
		else if (lex->supatok[var->z + var->i] == TOKEN_REDIR_E2)
		{
			did_fail |= delimiteur(lex, var);
			close (fd_e);
			fd_e = open("tmp/tmp.txt", O_RDWR, 0777);
		}
		if (var->z > 0)
			lex->s[var->z - 1] = add_after_redir(lex->s[var->z - 1],
					lex->s[var->z + var->i + 1]);
		var->i = var->i + 2;
	}
	if (lex->supatok[var->z - 1] == TOKEN_BUILTIN_OUTP)
	{
		if (fd_s != -2 && find_cmd_path(var, lex->s[var->z - 1][0]) != 0)
			dup2(fd_s, STDOUT_FILENO);
		exec_builtin_out(lex->s[var->z - 1], var, lex);
		dup2(fdtmp, STDOUT_FILENO);
		var->z = var->z + 1 + var->i;
	}
	else if (var->z > 0 && did_fail == 0)
	{	
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
		{
			if (var->last_pipe == 1)
				dup2(var->fd, STDIN_FILENO);
			if (var->z > 1 && lex->supatok[var->z - 2] == TOKEN_PIPE)
				dup2(var->fd, STDIN_FILENO);
			if (var->z > 2 && lex->supatok[var->z - 2] == TOKEN_PIPE
				&& lex->supatok[var->z - 3] == TOKEN_BUILTIN_OUTP)
			{
				var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
				dup2(var->fd, STDIN_FILENO);
			}
			if (fd_e != -2)
				dup2(fd_e, STDIN_FILENO);
			if (fd_s != -2 && find_cmd_path(var, lex->s[var->z - 1][0]) != 0)
				dup2(fd_s, STDOUT_FILENO);
			executeur(lex->s[var->z - 1], g_global.cpyenv, var);
		}
		else
		{
			var->pidnum++;
			if (var->z + 1 + var->i >= ft_malloc(lex) - 2)
			{
				if (var->fd != 0)
					close(var->fd);
				wait_pid(var, pip);
			}
			g_global.is_in_cat = 0;
			var->z = var->z + 1 + var->i;
			var->last_pipe = 0;
		}
	}
	else if (lex->supatok[var->z - 2] == TOKEN_BUILTIN_OUTP)
	{
		var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
		dup2(var->fd, STDIN_FILENO);
	}
	else
		var->z = var->z + 1 + var->i;
	return (1);
}

int	exe_s(t_lex *lex, t_var *var, t_pipe *pip, char **envp)
{	
	if (var->c == 0)
	{	
		var->c++;
		var->z = 0;
	}
	var->i = 0;
	if (lex->s[var->z] == NULL)
	{
		free_final(lex, pip, var);
		return (0);
	}
	while (var->z < ft_malloc(lex) - 1)
	{
		if (lex->supatok[var->z] == TOKEN_WORD)
		{
			if (lex->s[var->z + 1] == NULL)
			{
				g_global.is_in_cat = 1;
				var->shell[var->pidnum] = fork();
				if (var->shell[var->pidnum] == 0)
				{
					if (var->last_pipe == 1
						|| lex->supatok[var->z - 1] == TOKEN_PIPE)
					{
						dup2(var->fd, STDIN_FILENO);
					}
					executeur_final(lex->s[var->z], g_global.cpyenv, var, lex);
				}
				else
				{
					if (var->fd != 0 && var->last_pipe != 1)
						close(var->fd);
					wait_pid(var, pip);
					g_global.is_in_cat = 0;
					var->last_err_com = WEXITSTATUS(pip->status);
					free_final(lex, pip, var);
					var->last_pipe = 0;
					return (0);
				}
			}
			else
				var->z++;
		}
		else if (lex->supatok[var->z] == TOKEN_BUILTIN
			&& lex->supatok[var->z + 1] == TOKEN_PIPE)
			var->z += 2;
		else if (var->z > 0 && lex->supatok[var->z] == TOKEN_BUILTIN
			&& lex->supatok[var->z - 1] == TOKEN_PIPE)
			var->z++;
		else if (lex->supatok[var->z] == TOKEN_BUILTIN && var->z == 0)
		{
			execve_builtin(lex->s[var->z], envp, var, lex);
			var->z++;
		}
		else if (lex->supatok[var->z] == TOKEN_BUILTIN_OUTP
			&& lex->s[var->z + 1] == NULL)
		{
			exec_builtin_out(lex->s[var->z], var, lex);
			var->z++;
		}
		else if (lex->supatok[var->z] == TOKEN_BUILTIN_OUTP)
			var->z++;
		else if (lex->supatok[var->z] == TOKEN_PIPE)
		{
			if (lex->s[var->z + 1] == NULL)
				var->last_pipe = 1;
			minipipe(pip, lex, var);
		}
		else if (lex->supatok[var->z] == TOKEN_REDIR_S
			|| lex->supatok[var->z] == TOKEN_REDIR_E
			|| lex->supatok[var->z] == TOKEN_REDIR_S2
			|| lex->supatok[var->z] == TOKEN_REDIR_E2)
		{
			miniredir_s(lex, var, pip);
			var->c = 0;
			var->i = 0;
		}
		else
			var->z++;
	}
	return (0);
}

void	process(char **env, t_var *var, int i)
{
	t_lex	lex;
	t_pipe	pip;

	(void)i;
	var->nopath = 0;
	var->line = NULL;
	if (var->last_pipe != 1)
		var->fd = 0;
	currpath(var);
	find_path(g_global.cpyenv, var);
	if (var->last_pipe == 1)
		var->line = readline(">");
	else
		var->line = readline(var->promt);
	var->c = 0;
	var->pidnum = 0;
	if (!var->line)
	{
		printf("exit\n");
		exit(0);
	}
	init_tab(&lex, var->line, var->cpyenv, var);
	tokenizer(&lex);
	lex.s = separate_tok(var, &lex, lex.s);
	lex.s = del_brak(lex.s);
	turbotokenizer(&lex);
	historyset(var, &lex);
	creat_pid(&lex, var);
	if (parsing_syntax(&lex) == 1)
		exe_s(&lex, var, &pip, env);
}

void	set_termios(int in_cmd)
{
	struct termios	tty;

	tcgetattr(1, &tty);
	if (in_cmd == 1)
	{
		tty.c_lflag |= ECHOCTL;
		tty.c_cc[VQUIT] = 034;
	}
	else
	{
		tty.c_lflag &= ~ECHOCTL;
		tty.c_cc[VQUIT] = 0;
	}
	tcsetattr(1, TCSANOW, &tty);
}

void	init_termios(void)
{
	struct termios	tty;

	tcgetattr(1, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tty.c_cc[VQUIT] = 0;
	tcsetattr(1, TCSANOW, &tty);
}

void	ctrlc(int sig)
{
	(void)sig;
	if (g_global.is_in_cat == 0 && g_global.is_in_heredoc == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_global.is_in_heredoc == 2)
		exit(1);
}

void	ctrlbs(int sig)
{	
	write(1, "Quit: 3", 7);
	(void)sig;
}

void	ctrld(int sig)
{
	(void)sig;
}

void	init_sign(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlbs);
	signal(SIGKILL, ctrld);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_global.cpyenv = ft_strcpy_env(g_global.cpyenv, envp);
	int i;

	i = 0;
	if (g_global.cpyenv[0] == NULL)
	{
		printf("\033[1;91mError: No environment detected\n");
		return (1);
	}
	g_global.last_err_com = 0;
	g_global.last_pipe = 0;
	g_global.check_pipe = 0;
	g_global.previous_line = NULL;
	init_sign();
	init_termios();
	while (1)
	{
		process(g_global.cpyenv, &g_global, i);
		i++;
	}
}
