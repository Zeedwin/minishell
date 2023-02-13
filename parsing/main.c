
#include "../includes/shell.h"
#include <termios.h>

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
	if (ft_strlen2(var->line) != 0 && testspace(var) == 1)
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
	t_pipe pip;
	//t_token *head = NULL;
	
	currpath(var);
	//historyset(var);
	find_path(envp, var);
	var->line = readline(var->promt);
	var->c = 0;
	historyset(var);
	init_tab(&lex, var->line); //apres ca la ligne de commande est decoupe dans lex.s1
	tokenizer(&lex);
	lex.s = separate_tok(var, &lex, lex.s);
	turbotokenizer(&lex);
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

int	minipipe(t_pipe	*pip, t_lex *lex, char **envp, t_var *var)
{
	int fd;

	fd = dup(0);
	while (lex->s[var->z + 2] != NULL && var->z < ft_malloc(lex) - 2)
	{
		pipe(pip->tube);		//refaire car tube pas sauvegarde assez 		
		pip->pid = fork();
		if (pip->pid == 0) 
		{
			dup2(fd, STDIN_FILENO);
			if (lex->supatok[var->z + 1] == TOKEN_PIPE)
				dup2(pip->tube[1], STDOUT_FILENO);
			close(pip->tube[0]);
			if (lex->s[var->z + 1] == NULL || lex->supatok[var->z + 1] == TOKEN_PIPE)
				executeur(lex->s[var->z], envp, var);
			else if (lex->supatok[var->z + 1] == TOKEN_REDIR_S)
			{
				miniredir_s(lex, var, envp, pip);
			}
		}
		else 
		{
			waitpid(pip->pid, &pip->status, 0);
			close(pip->tube[1]);
			fd = pip->tube[0];
			var->z = var->z + 2;
			
		}
	}
	if (var->z >= ft_malloc(lex) - 2 && lex->s[var->z + 1] == NULL && var->c == 1)
	{	
		free_final(lex, pip, var);
		process(var, envp);
	}
	return (1);
}

void exe_s(t_lex *lex, t_var *var, t_pipe *pip, char **envp)
{
	if (var->c == 0)
	{	
		var->c++;
		var->z = 0;
	}
	var->i = 0;
	minipipe(pip, lex, envp, var);
	
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

	if (var->z < ft_malloc(lex) - 1)
	{	
		while(lex->supatok[var->z + 1 + var->i] == TOKEN_REDIR_S)
		{
			var->i = var->i + 2;
			fd = open(lex->s[var->z + var->i][0], O_CREAT | O_RDWR | O_TRUNC, 0777);
			lex->s[var->z] = add_after_redir(lex->s[var->z], lex->s[var->z + var->i]);
		}
		fd = open(lex->s[var->z + var->i][0], O_CREAT | O_RDWR | O_TRUNC, 0777);
		red = fork();
		if (red == 0)
		{
			if (find_cmd_path(var, lex->s[var->z][0]) != 0)
				dup2(fd, STDOUT_FILENO);
			executeur(lex->s[var->z], envp, var);
		}
		else
		{
			var->z = var->z + 2 + var->i;
			waitpid(red, &pip->status, 0);
			if (lex->s[var->z + 1] != NULL)
				exe_s(lex, var, pip, envp);
			else
			{	
				free_final(lex, pip, var);
				process(var, envp);
				exit(1);
			}
		}
	}
	return (1);
}

/*void miniredir_e(t_lex *lex, t_var *var char **envp, t_pipe *pip)
{
	int fd;
	pid_t red;

	if(lex->supatok[var->z + 1] == TOKEN_REDIR_E)
	{
		if (lex->s[var->z][1] != NULL)
		{
			while(lex->supatok[var->z + 1 + var->i] == TOKEN_REDIR_E)
			{
				
			}
		}
	}
}*/


void	set_termios(int in_cmd)
{
	struct termios	tty;

	tcgetattr(1, &tty);
	if (in_cmd == 1)
	{
		tty.c_lflag |= ECHOCTL;
		tty.c_cc[VQUIT] = 034;
	}
	else
	{
		tty.c_lflag &= ~ECHOCTL;
		tty.c_cc[VQUIT] = 0;
	}
	tcsetattr(1, TCSANOW, &tty);
}

void	init_termios(void)
{
	struct termios	tty;

	tcgetattr(1, &tty);
	tty.c_lflag &= ~ECHOCTL;
	tty.c_cc[VQUIT] = 0;
	tcsetattr(1, TCSANOW, &tty);
}

void ctrlc(int sig)
{
	(void)	sig;
	
	printf("\n");
	//rl_replace_line("", 0); //-lreadline -L ~/.brew/opt/readline/lib
	//rl_on_new_line();
	//if (gstruct->is_cmd == 0)
	//rl_redisplay();
}

void ctrlbs(int sig)
{
	(void)	sig;
	//gstruct->value_of_return = 131;
	
	write(2, "Quit: 3", 7);
}

void	init_sign(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlbs);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var var;
	
	var.c = 0;
	//t_lex *lex;
	init_sign();
	init_termios();
	process(&var, envp); 
	//echo(&var);
	
}