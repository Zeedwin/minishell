#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include "includes/shell.h"

void	minishellpipe(t_pipe	*pip, t_lex *lex, char **envp, t_var *var)
{	
	int i;
	int j;
	int z;

	j = count_pipe(lex->supatok, lex);
	i = 0;
	z = 2;
	pip->prevpipe = dup(0);
	//pip->cmd1 = open(lex.s[i], O_RDONLY);
	if (j >= 1)
	{
		pip->pipe[i] = malloc(2);
		pipe(pip->pipe[i]);
		pip->pid = fork();
		if (pip->pid == 0)
		{
			close(pip->pipe[i][0]);
			dup2(STDOUT_FILENO, pip->pipe[i][1]);
			close(pip->pipe[i][1]);
			dup2(STDIN_FILENO, pip->prevpipe);
			close(pip->prevpipe);
			executeur(lex->s[i], envp, var);
		}
		else
		{
			close(pip->pipe[i][1]);
			dup2(pip->prevpipe, pip->pipe[i][0]);
		}
		while(lex->supatok[z + 1] == TOKEN_PIPE)
		{
			i++;
			pip->pipe[i] = malloc(2);
			pipe(pip->pipe[i]);
			pip->pid = fork();
			if (pip->pid == 0)
			{
				close(pip->pipe[i][0]);
				dup2(STDOUT_FILENO, pip->pipe[i][1]);
				close(pip->pipe[i][1]);
				dup2(STDIN_FILENO, pip->pipe[i - 1][0]);
				close(pip->pipe[i - 1][0]);
				executeur(lex->s[z], envp, var);
			}
			else
			{
				close(pip->pipe[i][1]);
				dup2(pip->pipe[i - 1][0], pip->pipe[i][0]);
			}
			z = z + 2;
		}
		i++;
		pip->pid = fork();
		if (pip->pid == 0)
		{
			dup2(STDIN_FILENO, pip->pipe[i - 1][1]);
			close(pip->pipe[i - 1][1]);
			executeur(lex->s[z], envp, var);
		}
		else
		{
			close(pip->pipe[i - 1][1]);
			waitpid(pip->pid, &pip->status, 0);
			process(var, envp);
		}

	}
} 