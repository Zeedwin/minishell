#include "../includes/shell.h"
/*
int	file_input_check(char *file)
{
	if(access(file, F_OK) == 0)
		return (1);
	else
		return (0);
}*/

int	exec_builtin_out(char **s, t_var *var)
{

	if(ft_strcmp(*s, "pwd") || ft_strcmp(*s, "PWD"))
	{
		pwd(var);
	}
	else if(ft_strcmp(*s, "env") || ft_strcmp(*s, "ENV"))
	{
		env(g_global.cpyenv);
	}	
	return(1);
}

int execve_builtin(char **s, char **envp, t_var *var)
{
	(void)envp;

	if (ft_strcmp(*s, "cd") == 0 || ft_strcmp(*s, "CD") == 0)
	{
		cd(s, var);
		//printf("sus\n");
	}
	if(ft_strcmp(*s, "export"))
		export(g_global.cpyenv, "sus");
//else if(ft_strcmp(*s, "pwd") || ft_strcmp(*s, "PWD"))
//		pwd(var);
		/*else if(ft_strcmp(s[i], "env") || ft_strcmp(s[i], "ENV"))
			env(envp);
		else if(ft_strcmp(s[i], "exit"))
			ft_exit();
		else if(ft_strcmp(s[i], "echo") || )
			echo(s[i]);
		else if(ft_strcmp(s[i], "export"))
			export(envp);
		else if(ft_strcmp(s[i], "unset"))
			unset(envp);*/
	return 0;
}

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