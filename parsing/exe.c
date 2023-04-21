#include "../includes/shell.h"
/*
int	file_input_check(char *file)
{
	if(access(file, F_OK) == 0)
		return (1);
	else
		return (0);
}*/

int	exec_builtin_out(char **s, t_lex *lex, t_var *var)
{

	if(ft_strcmp(*s, "pwd") == 0 || ft_strcmp(*s, "PWD") == 0)
	{
		pwd();
	}
	else if(ft_strcmp(*s, "env") == 0 || ft_strcmp(*s, "ENV") == 0)
	{
		env(g_global.cpyenv);
	}
	else if(ft_strcmp(*s, "echo") == 0 || ft_strcmp(*s, "echo -n") == 0)
	{
		echo(var, lex);
	}

	return(1);
}

int execve_builtin(char **s, char **envp, t_var *var, t_lex *lex)
{
	(void)envp;

	if (ft_strcmp(*s, "cd") == 0 || ft_strcmp(*s, "CD") == 0)
	{
		cd(s, var);
		//printf("sus\n");
	}
	if(ft_strcmp(*s, "export") == 0)
	{
		fflush(stdout);
		g_global.cpyenv = export(g_global.cpyenv, lex->s[var->z][1]);
	}
	if(ft_strcmp(*s, "unset") == 0)
		g_global.cpyenv = unset(g_global.cpyenv, lex->s[var->z][1]);
	/*if(ft_strcmp(*s, "pwd") == 0|| ft_strcmp(*s, "PWD") == 0 )
		pwd(var);
	if(ft_strcmp(*s, "env") == 0|| ft_strcmp(*s, "ENV") == 0)
		env(envp);
	if(ft_strcmp(*s, "exit") == 0)
		ft_exit();
	if(ft_strcmp(*s, "echo") == 0)
		echo(*s);
	if(ft_strcmp(*s, "export") == 0)
		export(envp);*/
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