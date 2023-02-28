#include "../includes/shell.h"

int ft_strstrlen(char **s)
{
	int i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i);
}

int check_endcmd(char a)
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

void init_cmd(t_var *var)
{
	int i;

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

int testspace(t_var *var)
{
	int i;

	i = 0;
	while (var->line[i] != '\0')
	{
		if (var->line[i] != ' ')
			return (1);
		i++;
	}
	return (0);
}

void historyset(t_var *var)
{
	if (ft_strlen2(var->line) != 0 && testspace(var) == 1)
		add_history(var->line);
}

int count_pipe(int *supatok, t_lex *lex)
{
	int i;
	int j;

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

int	minipipe(t_pipe	*pip, t_lex *lex, char **envp, t_var *var)
{
	if (var->c == 1)
	{
		var->c++;
		var->fd = dup(0);
	}
	pipe(pip->tube);		   		
	pip->pid = fork();
	if (pip->pid == 0) 
	{
		dup2(var->fd, STDIN_FILENO);
		dup2(pip->tube[1], STDOUT_FILENO);
		close(pip->tube[0]);
		executeur(lex->s[var->z], envp, var);
		return (0);
	}
	else
	{
		waitpid(pip->pid, &pip->status, 0);
		close(pip->tube[1]);
		var->fd = pip->tube[0];
		var->z +=2;
		return (1);
	}
}

char **add_after_redir(char **s1, char **s2)
{
	int i;
	int j;
	char **s3;

	i = 0;
	j = 1;
	s3 = malloc(sizeof(char *) * (ft_strstrlen(s1) + ft_strstrlen(s2)));
	while(s1[i] != NULL)
	{
		s3[i] = malloc(sizeof(char) * (ft_strlen(s1[i]) + 1));
		s3[i] = ft_strcpy(s3[i], s1[i]);
		i++;
	}
	while(s2[j] != NULL)
	{
		s3[i] = malloc(sizeof(char) * (ft_strlen(s2[j]) + 1));
		s3[i] = ft_strcpy(s3[i], s2[j]);
		i++;
		j++;
	}
	s3[i] = NULL;
	return (s3);
}


int miniredir_s(t_lex *lex, t_var *var, char **envp, t_pipe *pip)
{
	int fd;
	pid_t red;
	
	fd = dup(0);
	if (lex->supatok[var->z - 1] == TOKEN_PIPE && var->z > 1)
		dup2(var->fd, STDIN_FILENO);
	while(lex->supatok[var->z + 1 + var->i] == TOKEN_REDIR_S)
	{
		var->i = var->i + 2;
		fd = open(lex->s[var->z + var->i][0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		lex->s[var->z] = add_after_redir(lex->s[var->z], lex->s[var->z + var->i]);
	}
	fd = open(lex->s[var->z + var->i][0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	red = fork();
	if (red == 0)
	{
		if (find_cmd_path(var, lex->s[var->z][0]) != 0)
		{
			printf("oi");
			fflush(stdout);
			dup2(fd, STDOUT_FILENO);
		}
		executeur(lex->s[var->z], envp, var);
	}
	else
	{
		waitpid(red, &pip->status, 0);
		if (lex->s[var->z + var->i + 1] != NULL)  
			var->z = var->z + 2 + var->i;
		else
			var->z = var->z + var->i;
	}
	return (1);
}

int exe_s(t_lex *lex, t_var *var, t_pipe *pip, char **envp)
{
	pid_t re;

	if (var->c == 0)
	{	
		var->c++;
		var->z = 0;
	}
	var->i = 0;
	if(lex->s[var->z] == NULL)
	{
		free_final(lex, pip, var);
		process(envp);
		return (0);
	}
	while (var->z < ft_malloc(lex) - 1)
	{
		if (lex->supatok[var->z + 1] == TOKEN_PIPE)
		{
			minipipe(pip, lex, envp, var);
		}
		else if (lex->supatok[var->z + 1] == TOKEN_REDIR_S)
		{
			miniredir_s(lex, var, envp, pip);
		}
		else if(lex->s[var->z + 1] == NULL)
		{
			re = fork();
			if (re == 0)
			{			
				executeur_final(lex->s[var->z], envp, var, lex);
				return (0);
			}
			else 
			{			
				waitpid(re, &pip->status, 0);
				free_final(lex, pip, var);
				process(envp);
				return (0);
			}
		}
	}
	return(0);
}

void process(char **envp)
{
	t_var var;
	t_lex lex;
	(void)envp;
	t_pipe pip;
	//t_token *head = NULL;
	var.c = 0;
	var.line = NULL;
	currpath(&var);
	//historyset(var);
	find_path(envp, &var);
	dup2(STDIN_FILENO, STDIN_FILENO);
	var.line = readline(var.promt);
	
	printf("->'%s'<-\n", var.line);
	var.c = 0;
	historyset(&var);
	init_tab(&lex, var.line); //apres ca la ligne de commande est decoupe dans lex.s1
	tokenizer(&lex);
	lex.s = separate_tok(&var, &lex, lex.s);
	turbotokenizer(&lex);
	exe_s(&lex, &var, &pip, envp);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	//t_lex *lex;
	process(envp); 
	//echo(&var);
}