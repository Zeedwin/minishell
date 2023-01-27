
#include "../includes/shell.h"


void	free_this(char **tab)
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
	//t_token *head = NULL;

	i = 0;
	currpath(var);
	find_path(envp, var);
	var->line = readline(var->promt);
	init_tab(&lex, var->line); //apres ca la ligne de commande est decoupe dans lex.s1
	tokenizer(&lex);
	lex.s = separate_tok(var, &lex, lex.s);
	turbotokenizer(&lex);
	/*while (lex.s[i])
	{
		if (lex.supatok[i + 1] == TOKEN_PIPE)
		{
			pipe()
			lex.pipe_out[i] = pipes[1];
			lex.pipe_in[i + 1] = pipes[0];
		}
	}*/
	//printf("oui");
	//fflush(stdout);
	printcharstar3(&lex);
	/*int	j;
	j = 0;
	while (lex.s1[j])
	{

		//printf("-> %s ->token = %d\n", lex.s1[j], lex.stoken[j]);
		j++;
	}*/
}



int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var var;
	//t_lex *lex;
	process(&var, envp); 
	//echo(&var);
	
}