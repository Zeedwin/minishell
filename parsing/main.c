/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:22:43 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/17 18:51:29 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <termios.h>

t_var	g_global;



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
	(void)sig;
	rl_on_new_line();
	rl_redisplay();
	g_global.last_err_com += 128;
}

void	init_sign(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlbs);
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
	//init_termios();
	while (1)
	{
		process(&g_global);
	}
}
