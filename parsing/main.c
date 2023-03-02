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
	pid_t ell;

	if (var->c == 0                                                                                                                                                                                                                                                                    )
	{
		var->c++;
		var->fd = dup(0);
	}
	pipe(pip->tube);		   		
	ell = fork();
	if (ell == 0) 
	{
		dup2(var->fd, STDIN_FILENO);
		dup2(pip->tube[1], STDOUT_FILENO);
		close(pip->tube[0]);
		executeur(lex->s[var->z - 1], envp, var);
	}
	else
	{
		waitpid(ell, &pip->status, 0);
		close(pip->tube[1]);
		var->fd = pip->tube[0];
		printf("fd = %d", var->fd);
		var->z +=1;
	}
	return(1);
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
	pid_t ll;
	
	
	while(lex->supatok[var->z + var->i] == TOKEN_REDIR_S)
	{
		fd = open(lex->s[var->z + var->i + 1][0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		if (var->z > 0)
			lex->s[var->z - 1] = add_after_redir(lex->s[var->z - 1], lex->s[var->z + var->i + 1]);
		var->i = var->i + 2;
	}
	if (find_cmd_path(var, lex->s[var->z - 1][0]) != 0 && var->z > 0)
	{	
		ll = fork();
		if (ll == 0)
		{
			if (lex->supatok[var->z - 2] == TOKEN_PIPE && var->z > 1)
				dup2(var->fd, STDIN_FILENO);
			dup2(fd, STDOUT_FILENO);
			executeur(lex->s[var->z - 1], envp, var);
		}
		else
		{
			waitpid(ll, &pip->status2, 0);
			var->z = var->z + 1 + var->i;

		}
	}
	else 
		var->z++;
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
		return (0);
	}
	printf("\n%d\n", ft_malloc(lex));
	while (var->z < ft_malloc(lex) - 1)
	{
		if (lex->supatok[var->z] == TOKEN_WORD)
		{
			if (lex->s[var->z + 1] == NULL)
			{
				re = fork();
				if (re == 0)	
					executeur_final(lex->s[var->z], envp, var, lex);
				else
				{
					waitpid(re, &pip->status, 0);
					free_final(lex, pip, var);
					return (0);
				}
			}
			else 
			{
				var->z++;
			}
		}
		if (lex->supatok[var->z] == TOKEN_PIPE)
		{
			minipipe(pip, lex, envp, var);	
		}
		if (lex->supatok[var->z] == TOKEN_REDIR_S)
		{
			miniredir_s(lex, var, envp, pip);
			var->c = 0;
			var->i = 0;
		}
		/*if (lex->supatok[var->z + 1] == TOKEN_PIPE)
		{
			printf("=====%s\n" , lex->s[var->z][0]);
			minipipe(pip, lex, envp, var);
		}
		else if (lex->supatok[var->z] == TOKEN_REDIR_S)
		{
			printf("=i====%s\n" , lex->s[var->z][0]);
			printf("oui");
			printf("oui321");
			miniredir_s(lex, var, envp, pip);
		}
		else if(lex->s[var->z + 1] == NULL)
		{
			printf("===l==%s\n" , lex->s[var->z][0]);
			re = fork();
			if (re == 0)
			{
				printf("op");
				executeur_final(lex->s[var->z], envp, var, lex);
			}
			else 
			{			
				waitpid(re, &pip->status1, 0);
				free_final(lex, pip, var);
				return (0);
			}
		}*/
	}
	return(0);
}

void process(char **envp)
{
	t_var var;
	t_lex lex;
	t_pipe pip;
	//t_token *head = NULL;
	var.c = 0;
	var.line = NULL;
	currpath(&var);
	//historyset(var);
	find_path(envp, &var);
	//char c;
	//int n = read(0, &c, 1);
	//printf("n = %d c = %c\n", n, c);
	var.line = readline(var.promt);
	printf("->'%s'<-\n", var.line);
	var.c = 0;
	if(var.line[0])
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
	while (1)
		process(envp); 
	//echo(&var);
}