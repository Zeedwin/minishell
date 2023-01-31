
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

void process(t_var *var, char **envp)
{
	t_lex lex;
	(void)envp;
	int i;
	t_pipe pip;
	//t_token *head = NULL;
	

	i = 0;
	currpath(var);
	//historyset(var);
	find_path(envp, var);
	var->line = readline(var->promt);
	//historyset(var);
	init_tab(&lex, var->line); //apres ca la ligne de commande est decoupe dans lex.s1
	tokenizer(&lex);
	lex.s = separate_tok(var, &lex, lex.s);
	turbotokenizer(&lex);
	pip.pipe = malloc((count_pipe(lex.supatok, &lex) + 1) *  sizeof(int *));
	exe_s(&lex, var, &pip, envp);
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


void	minipipe(t_pipe	*pip, t_lex *lex, char **envp, t_var *var)
{	
	int i;

	i = 0;
	pip->prevpipe = dup(0);
	if (lex->supatok[var->z + 1] == TOKEN_PIPE)
	{
		var->z = var->z + 2;
		pip->pipe[i] = malloc(2);
		pipe(pip->pipe[i]);
		pip->pid = fork();
		if (pip->pid == 0)
		{
			close(pip->pipe[i][0]);
			dup2(pip->pipe[i][1], STDOUT_FILENO);
			close(pip->pipe[i][1]);
			dup2(pip->prevpipe, STDIN_FILENO);
			close(pip->prevpipe);
			executeur(lex->s[var->z], envp, var);
		}
		else
		{
			close(pip->pipe[i][1]);
			close(pip->prevpipe);
			pip->pipe[i][0] = pip->prevpipe;
		}
		while(lex->supatok[var->z + 1] == TOKEN_PIPE)
		{
			i++;
			pip->pipe[i] = malloc(2);
			pipe(pip->pipe[i]);
			pip->pid = fork();
			if (pip->pid == 0)
			{
				close(pip->pipe[i][0]);
				dup2(pip->pipe[i][1], STDOUT_FILENO);
				close(pip->pipe[i][1]);
				dup2(pip->pipe[i - 1][0], STDIN_FILENO);
				close(pip->pipe[i - 1][0]);
				executeur(lex->s[var->z], envp, var);
			}
			else
			{
				close(pip->pipe[i][1]);
				close(pip->pipe[i - 1][0]);
				pip->pipe[i][0] = pip->pipe[i][1];
			}
			var->z = var->z + 2;
		}
		i++;
		if (lex->s[var->z + 1] != TOKEN_REDIR)	
			pip->pid = fork();
			if (pip->pid == 0)
			{
				dup2(pip->pipe[i - 1][0], STDIN_FILENO);
				close(pip->pipe[i - 1][0]);
				executeur(lex->s[var->z], envp, var);
			}
			else
			{
				close(pip->pipe[i - 1][1]);
				waitpid(pip->pid, &pip->status, 0);
				free_final(lex, pip);
				process(var, envp);
			}
	}
} 

void exe_s(t_lex *lex, t_var *var, t_pipe *pip, char **envp)
{
	var->z = 0;
	while (lex->s[var->z])
	{
		minipipe(pip, lex, envp, var);
		if (lex->s[var->z + 1] == NULL && lex->s[var->z])
		{
			pip->pid = fork();
			if (pip->pid == 0)
				executeur(lex->s[var->z], envp, var);
			else 
			{
				waitpid(pip->pid, &pip->status, 0);
				free_final(lex, pip);
				process(var, envp);
			}
		}
	}
}

void miniredir(t_lex *lex, t_var *var, char **envp)
{
	int i;

	i = 0;
	
	if(lex->supatok[i + 1] == TOKEN_REDIR)
	{	
		fd = open(lex->s[i + 1], O_CREAT, O_RDWR, O_TRUNC, 0777);
		dup2(STDOUT_FILENO, fd[1])
		dup2(fd[1]);
		close(fd[0]);
		
		
		i++;
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