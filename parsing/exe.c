#include "../includes/shell.h"
/*
int	file_input_check(char *file)
{
	if(access(file, F_OK) == 0)
		return (1);
	else
		return (0);
}*/

int	exec_builtin_out(char **s, t_var *var, t_lex *lex)
{

	if(ft_strcmp(*s, "pwd") == 0 || ft_strcmp(*s, "PWD") == 0)
	{
		pwd();
	}
	else if(ft_strcmp(*s, "env") == 0 || ft_strcmp(*s, "ENV") == 0)
	{
		env(g_global.cpyenv);
	}
	else if(ft_strcmp(*s, "echo") == 0)
	{
		echo(var, lex);
	}
	return(1);
}

int execve_builtin(char **s, char **env, t_var *var, t_lex *lex)
{
	(void)env;

	if (ft_strcmp(*s, "cd") == 0 || ft_strcmp(*s, "CD") == 0)
		cd(s, var);
	if(ft_strcmp(*s, "export") == 0)
		g_global.cpyenv = export(g_global.cpyenv, lex, var);
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
		export(envp);
	if(ft_strcmp(*s, "unset") == 0)
		unset(envp);*/
	return 0;
}

char *check_doc(char *s)
{
	int j;
	int i;
	char *s1;

	i = 0;
	while(s[i] != '\0')
	{
		i++;
	}
	s1 = malloc(sizeof(char) * (i - 1));
	i = 0;
	j = 2;
	while(s[j] != '\0')
	{
		s1[i] = s[j];
		j++;
		i++;
	}
	s1[i] = '\0';
	i = open(s1, O_RDWR, 0777);
	if (i == -1 && errno == ENOENT)
		return(0);
	close(i);
	return(s1);

}

char *check_replace_prog(char *s, t_var *var)
{
	char *s1;
	int i;
	int j;

	i = 0;
	j = 0;
	s1 = NULL;
	if(s[0] == '.')
	{
		if(s[1] == '/')
		{
			if(check_doc(s) != 0)
			{
				s = check_doc(s);
				s1 = malloc(sizeof(char) * (ft_strlen(var->line) + ft_strlen(s)));
				printf("line  = %s", var->line);
				while(var->line[i] != '\0')
				{
					s1[i] = var->line[i];
					i++;
				}
				s1[i] = '/';
				i++;
				while(s[j] != '\0')
				{
					s1[i] = s[j];
					i++;
					j++;
				}
				s1[i] = '\0';
			}
			else
			{
				return(0);
			} 
		}
	}
	return(s);	
}

void executeur(char **s, char **env, t_var *var)
{
	char *cmdpath;

	//printf("%s\n", var->path);
	printf("lol");
	fflush(stdout);
	cmdpath = find_cmd_path(var, s[0]);
	if(var->nopath == 0)
		cmdpath = 0;
	if (cmdpath == 0)
	{
		if (s[0][1] == '.' && s[0][1] == '.' && s[0][2] == '/')
			printf("minishell: no such file or directory: %s\n", s[0]);
		else 
			printf("bash : %s: command not found\n", s[0]);
		exit(1);
	}
	execve(cmdpath, s, env);
}

void executeur_final(char **s, char **env, t_var *var, t_lex *lex)
{
	char *cmdpath;

	if (var->z > 0 && lex->supatok[var->z - 1] == TOKEN_PIPE)
		dup2(var->fd, STDIN_FILENO);
	if (lex->supatok[var->z - 1] == TOKEN_PIPE && lex->supatok[var->z - 2] == TOKEN_BUILTIN_OUTP)
	{
		var->fd = open("tmp/tmp.txt", O_RDWR, 0777);
		dup2(var->fd, STDIN_FILENO);
	}
	cmdpath = find_cmd_path(var, s[0]);
	dup2(var->fd, STDOUT_FILENO);
	if(var->nopath == 0)
		cmdpath = 0;
	if (cmdpath == 0)
	{
		if (s[0][1] == '.' && s[0][1] == '.' && s[0][2] == '/')
			printf("minishell: no such file or directory: %s\n", s[0]);
		else 
			printf("bash : %s: command not found\n", s[0]);
		exit(1);
	}
	s[0] = remo_slash(s[0]);
	execve(cmdpath, s, env);
}