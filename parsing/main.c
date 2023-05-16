/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:22:43 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/16 14:56:09 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <termios.h>

t_var	g_global;

int	exe_s(t_lex *lex, t_var *var, t_pipe *pip)
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
	var->fd = dup(0);
	while (var->z < ft_malloc(lex) - 1 - var->check_after_redir)
	{
		if (lex->supatok[var->z] == TOKEN_WORD && lex->s[var->z] != NULL)
		{
			if (lex->s[var->z + 1] == NULL)
			{
				g_global.is_in_cat = 1;
				var->shell[var->pidnum] = fork();
				if (var->shell[var->pidnum] == 0)
				{
					if (var->z > 0 && (var->last_pipe == 1
							|| lex->supatok[var->z - 1] == TOKEN_PIPE))
					{
						dup2(var->fd, STDIN_FILENO);
					}
					executeur_final(lex->s[var->z], g_global.cpyenv, var, lex);
				}
				else
				{
					if (var->fd != 0 && var->last_pipe != 1)
						close(var->fd);
					//if (var->no_wait == 0)
					wait_pid(var, pip);
					g_global.is_in_cat = 0;
					if (g_global.exitcode == 130)
						var->last_err_com = 130;
					if (g_global.lacontedetagrandmere > 0)
					{
						var->last_err_com = 130;
						g_global.lacontedetagrandmere = 0;
					}
					else if (g_global.exitcode == 0)
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
			execve_builtin(lex->s[var->z], var, lex);
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
			{
				var->last_pipe = 1;
			}
			var->fail_dir = 0;
			minipipe(pip, lex, var);
		}
		else if (lex->supatok[var->z] == TOKEN_REDIR_S
			|| lex->supatok[var->z] == TOKEN_REDIR_E
			|| lex->supatok[var->z] == TOKEN_REDIR_S2
			|| lex->supatok[var->z] == TOKEN_REDIR_E2)
		{
			miniredir_s(lex, var, pip);
			var->fail_dir = 0;
			var->c = 0;
			var->i = 0;
		}
		else
			var->z++;
	}
	free_final(lex, pip, var);
	return (0);
}

void	process(t_var *var)
{
	t_lex	lex;
	t_pipe	pip;
	char	*lineread;

	var->count_wait = 0;
	var->check_after_redir = 0;
	var->nopath = 0;
	var->fail_dir = 0;
	var->line = NULL;
	if(var->path != NULL)
		var->path = NULL;
	lineread = NULL;
	var->last_pipe = 0;
	if (var->last_pipe != 1)
		var->fd = 0;
	if (g_global.lacontedetagrandmere > 0)
	{
		var->last_err_com = 130;
		g_global.lacontedetagrandmere = 0;
	}
	g_global.is_in_heredoc = 0;
	currpath(var);
	find_path(g_global.cpyenv, var);
	if (var->last_pipe == 1)
		lineread = readline(">");
	else
		lineread = readline(var->promt);
	if (!lineread)
	{
		printf("exit\n");
		exit(0);
	}
	var->line = malloc(sizeof(char) * (ft_strlen(lineread) + 1));
	var->line = ft_strcpy(var->line, lineread);
	add_history(var->line);
	var->c = 0;
	var->pidnum = 0;
	init_tab(&lex, var->line, var->cpyenv, var);
	tokenizer(&lex);
	lex.s = separate_tok(var, &lex, lex.s);
	lex.s = del_brak(lex.s);
	turbotokenizer(&lex);
	//historyset(var, &lex);
	creat_pid(&lex, var);
	if (parsing_syntax(&lex) == 1)
		exe_s(&lex, var, &pip);
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

	if(g_global.is_in_heredoc != 0 && g_global.lacontedetagrandmere == 0)
		g_global.lacontedetagrandmere += 1;
	if (g_global.is_in_cat == 0 && g_global.is_in_heredoc == 0)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else if (g_global.is_in_heredoc == 2)
	{
		printf("dsdasd\n");
		g_global.exitcode = 130;
	//	g_global.lacontedetagrandmere += 1;
		exit(130);
	}
	else if (g_global.is_in_cat != 0)
		g_global.lacontedetagrandmere += 1;
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
	if (g_global.cpyenv[0] == NULL)
	{
		printf("\033[1;91mError: No environment detected\n");
		return (1);
	}
	g_global.exitcode = 0;
	g_global.last_err_com = 0;
	g_global.last_pipe = 0;
	g_global.is_in_heredoc = 0;
	g_global.check_pipe = 0;
	g_global.previous_line = NULL;
	init_sign();
	init_termios();
	while (1)
	{
		process(&g_global);
	}
}
