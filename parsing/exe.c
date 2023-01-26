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