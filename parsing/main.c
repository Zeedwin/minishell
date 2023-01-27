
#include "../includes/shell.h"


void	E3free_this(char **tab)
{
	int	x;

	x = 0;
	while (tab[x] != NULL)
	{
		free(tab[x]);
		x++;
	}
	free(tab);
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
	if (ft_strlen(var->line) != 0 && testspace(var) == 1)
		add_history(var->line);
}

void	cmd1_process(t_var *var, char **envp)
{
	currpath(var);
	var->line = readline(var->promt);
	historyset(var);
	init_cmd(var);
	find_path(envp, var);
	var->cmdpath = var->cmd1[0];
	ft_exit(var);
	if (access(var->cmd1[0], F_OK | X_OK) != 0)
		var->cmdpath = find_cmd_path(var, var->cmd1[0]);
	if (var->cmdpath == 0)
	{
		if (ft_strlen(var->line) != 0 && testspace(var) == 1)
			printf("bash: %s: command not found\n",var->line);
		cmd1_process(var, envp);
	}
	else
	{
		var->shell = fork();
		if (var->shell == 0)
			execve(var->cmdpath, var->cmd1, envp);
		waitpid(var->shell, NULL, 0);
		if (var->shell != 0)
		{
			cd(var);
			cmd1_process(var, envp);
		}
	}

}

void printcharstar3(t_lex *lex)
{
	int i;
	int j;
	//int k;

	i = 0;
	j = 0;
	//k = 0;
	//printf("s0 = %p\n", s[0]);
	while (lex->s[i])
	{
		j = 0;
		printf("Num of char **: %d\n", i);
		printf("-------------------\n");
		while (lex->s[i][j])
		{
			printf("Char *%p: %s, pos: %d and token%d\n", lex->s[i][j], lex->s[i][j], j, lex->supatok[i]);
			j++;
		}
			printf("-------------------\n");
		
		//j++;
		i++;
	}
}

// 0x20 [1] = NULL
// 0x21
// 0x22


/*void dew(char ***cmd) {
	int i = 0;
	int pipes[2];

	while (cmd[i])
	{
		if (cmd[i+1] != NULL) {
			pipe(pipes);
		}
		fork()
		if (pid== 0) {
			if (pipes[0])
				dup2()
			if (pipes[1])
			exevc
		}
	}
}*/


void process(t_var *var, char **envp)
{
	t_lex lex;
	(void)envp;
	int i;
	t_pipe pip;
	//t_token *head = NULL;

	i = 0;
	currpath(var);
	find_path(envp, var);
	var->line = readline(var->promt);
	init_tab(&lex, var->line); //apres ca la ligne de commande est decoupe dans lex.s1
	tokenizer(&lex);
	lex.s = separate_tok(var, &lex, lex.s);
	turbotokenizer(&lex);
	minishellpipe(pip, lex, envp);
	//if (pip.pid != 0)
	//	process(var, envp);	
	/*while (lex.s[i])
	{
		if (lex.supatok[i + 1] == TOKEN_PIPE)
		{
			pipe(pi)
		}
	}*/
	//printf("oui");
	//fflush(stdout);
	//printcharstar3(&lex);
	/*int	j;
	j = 0;
	while (lex.s1[j])
	{

		//printf("-> %s ->token = %d\n", lex.s1[j], lex.stoken[j]);
		j++;
	}*/
}


void	minishellpipe(t_pipe	*pip, t_lex *lex, char **envp)
{	
	int i;
	int res;

	if (var->c == 0)
	{
		pip->firstcmd = open(lex->s[0], O_RDONLY);
		var->c++;
	}
	i = 0;
	while(lex->s[i])
	{
		pip->cmd2 = open(lex->s[i + 2], O_RDONLY);
		if (lex->supatok[i + 1] == TOKEN_PIPE)
		{
			
			pip->cmd2 = open(lex->s[i + 2], O_RDWR);
			pipe(pip->pipe); //on a pipe[0] et pipe [1]
			pip->pid = fork();
			fork_error(pip.pid);
			if (pip->pid == 0)
			{
				dup2(pip->cmd1[1], cmd2[0]);
				close(pip->cmd1[0]);
				close(pip->cmd2[1]);
				//dup2(infile, 0);
				res = executeur(lex->s[i], envp, var);
				if(res == -1)
				{
					perror("execve");
				}
			}
			if (pip->pid != 0)
			{
				dup2(pip->cmd1[0], cmd2[1]);
				close(pip->cmd1[1]);
				close(pip->cmd2[0]);
				res = proce
				if (res == -1)
				{
					perror("execve");
				}
			}
		}
		else
		{
			pip.pid = fork();
			if (pip.pid == 0)
				executeur(lex.s[0], envp, var);
			waitpid(pip.pid, NULL, 0);
			free_final(&lex);
			if (pip.pid != 0)
				process(var, envp);
		}
		i = i + 2;
	}
}


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var var;

	var.c = 0;
	//t_lex *lex;
	process(&var, envp); 
	//echo(&var);
	
}