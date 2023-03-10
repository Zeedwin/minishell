#include "../includes/shell.h"



void executeur(char **s, char **envp, t_var *var)
{
	char *cmdpath;

	cmdpath = find_cmd_path(var, s[0]);
	if (cmdpath == 0)
	{
		printf("bash : %s: command not found\n", s[0]);
		fflush(stdout);
		exit(1);
	}
	execve(cmdpath, s, envp);
}

void executeur_final(char **s, char **envp, t_var *var, t_lex *lex)
{
	char *cmdpath;

	if (var->z > 0 && lex->supatok[var->z - 1] == TOKEN_PIPE)
		dup2(var->fd, STDIN_FILENO);
	cmdpath = find_cmd_path(var, s[0]);
	if (cmdpath == 0)
	{
		printf("bash : %s: command not found\n", s[0]);
		fflush(stdout);
		exit(1);
	}
	execve(cmdpath, s, envp);
}