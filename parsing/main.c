/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:20:28 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 13:41:24 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include <termios.h>

t_var	g_global;

void	process_ini(t_var *var)
{
	var->count_wait = 0;
	var->check_after_redir = 0;
	var->nopath = 0;
	var->fail_dir = 0;
	var->line = NULL;
	if (var->path != NULL)
		var->path = NULL;
	var->last_pipe = 0;
	if (var->last_pipe != 1)
		var->fd = 0;
	if (g_global.lacontedetagrandmere > 0)
	{
		var->last_err_com = 130;
		g_global.lacontedetagrandmere = 0;
	}
	g_global.is_in_heredoc = 0;
}

void	process(t_var *var)
{
	t_lex	lex;
	t_pipe	pip;
	char	*lineread;

	
	(n(), lineread = NULL, var->bowlingboolean = 0);
	(n(), process_ini(var), currpath(var), find_path(var->cpyenv, var));
	if (var->last_pipe == 1)
		lineread = readline(">");
	else
		lineread = readline(var->promt);
	if (!lineread)
	{
		free_final_d(&pip, var);
		printf("exit\n");
		exit(0);
	}
	var->line = malloc(sizeof(char) * (ft_strlen(lineread) + 1));
	(n(), var->line = ft_strcpy(var->line, lineread));
	if (check_empty(var->line) == 1)
		add_history(var->line);
	(n(), var->pidnum = 0, process_init(&lex, var));
	if (parsing_syntax(&lex) == 1)
		exe_s(&lex, var, &pip);
	else
		free_final(&lex, &pip, var);
}

void	ctrlc(int sig)
{
	(void)sig;
	if (g_global.is_in_heredoc != 0 && g_global.lacontedetagrandmere == 0)
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
		g_global.exitcode = 130;
		exit(130);
	}
	else if (g_global.is_in_cat != 0)
		g_global.lacontedetagrandmere += 1;
}

void	ctrlbs(int sig)
{	
	(void)sig;
	if (g_global.is_in_cat != 0)
	{
		printf("^\\Quit 3\n");
	}
	else
	{
		rl_on_new_line();
		rl_redisplay();
	}
}

int	main(int ac, char **av, char **envp)
{
	struct termios	tty;

	tcgetattr(1, &tty);
	tty.c_lflag &= ~ECHOCTL;
	(void)ac;
	(void)av;
	g_global.cpyenv = ft_strcpy_env(g_global.cpyenv, envp);
	if (g_global.cpyenv[0] == NULL)
	{
		printf("\033[1;91mError: No environment detected\n");
		return (0);
	}
	g_global.exitcode = 0;
	g_global.last_err_com = 0;
	g_global.last_pipe = 0;
	g_global.is_in_heredoc = 0;
	g_global.check_pipe = 0;
	g_global.previous_line = NULL;
	init_sign();
	while (1)
	{
		tcsetattr(1, TCSANOW, &tty);
		process(&g_global);
	}
}
