#include "../includes/shell.h"
#include <termios.h>

char	*ft_realloc(char *map, int i)
{
	char	*map_tp;
	int		x;

	x = 0;
	map_tp = malloc(i * sizeof(char *));
	while (map[x])
	{
		map_tp[x] = map[x];
		x++;
	}
	free(map);
	map_tp[x] = '\0';
	return (map_tp);
}

char	**ft_realloc2(char **map, int i)
{
	char	**map_tp;
	int		x;

	x = 0;
	map_tp = malloc(i * sizeof(char *));
	while (map[x])
	{
		map_tp[x] = ft_strcpy(map_tp[x], map[x]);
		x++;
	}
	free(map);
	map_tp[x] = NULL;
	return (map_tp);
}

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

void historyset(t_var *var, t_lex *lex)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (var->previous_line == NULL)
		var->previous_line = ft_strdup(var->line);
	if (var->check_pipe == 1)
	{
		while(var->previous_line[i] != '\0')
		{
			i++;
		}
		var->previous_line = ft_realloc(var->previous_line, (ft_strlen(var->line) + ft_strlen(var->previous_line) + 1));
		while(var->line[j] != '\0')
		{
			var->previous_line[i] = var->line[j];
			i++;
			j++;
		}
		var->previous_line[i] = '\0';
		if (lex->supatok[ft_malloc(lex) - 3] != TOKEN_PIPE)
		{
			var->check_pipe = 0;
			add_history(var->previous_line);
		}
		
	}
	else if (lex->supatok[ft_malloc(lex) - 3] == TOKEN_PIPE)
	{
		var->check_pipe = 1;
	}
	else if (ft_strlen2(var->line) != 0 && testspace(var) == 1 && var->check_pipe == 0 )
	{
		add_history(var->line);
		var->previous_line = ft_strdup(var->line);
	}
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
int delimiteur(t_lex *lex,t_var *var)
{
	char buffer[BUF_SIZE];
	char *s;
	int fd;
	ssize_t num_read;

	num_read = 0;
	fd = open("tmp/tmp.txt", O_CREAT | O_RDWR | O_TRUNC, 0777);
	while (1)
	{
			num_read = read(STDIN_FILENO, buffer, BUF_SIZE);
			s = del_backn(buffer);
			if (ft_strcmp(s, lex->s[var->z + var->i + 1][0]) == 0)
			{
				close(fd);
				return(0);
			}
    	    write(fd, buffer, num_read);
    }
    close(fd);
    return 0;
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
		if (find_cmd_path(var, lex->s[var->z - 1][0]) != 0)	
			dup2(pip->tube[1], STDOUT_FILENO);
		close(pip->tube[0]);
		executeur(lex->s[var->z - 1], envp, var);
	}
	else
	{
		waitpid(ell, &pip->status, 0);
		close(pip->tube[1]);
		var->fd = pip->tube[0];
		//printf("fd = %d", var->fd);
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
	int fd_e;
	int fd_s;
	pid_t ll;
	
	fd_e = -2;
	fd_s = -2;
	while(lex->supatok[var->z + var->i] == TOKEN_REDIR_S || lex->supatok[var->z + var->i] == TOKEN_REDIR_E
		|| lex->supatok[var->z + var->i] == TOKEN_REDIR_S2 || lex->supatok[var->z + var->i] == TOKEN_REDIR_E2)
	{
		if (lex->supatok[var->z + var->i] == TOKEN_REDIR_S)
		{
			close(fd_s);
			fd_s = open(lex->s[var->z + var->i + 1][0], O_CREAT | O_WRONLY | O_TRUNC, 0777);
		}
		if (lex->supatok[var->z + var->i] == TOKEN_REDIR_E)
		{
			close(fd_e);
			fd_e = open(lex->s[var->z + var->i + 1][0], O_RDWR, 0777);
		}
		if (lex->supatok[var->z + var->i] == TOKEN_REDIR_S2)
		{
			close (fd_s);
			fd_s = open(lex->s[var->z + var->i + 1][0], O_CREAT | O_APPEND | O_WRONLY, 0777);
		}
		if (lex->supatok[var->z + var->i] == TOKEN_REDIR_E2)
		{
			delimiteur(lex, var);
			close (fd_e);
			fd_e = open("tmp/tmp.txt", O_RDWR, 0777);
		}
		if (var->z > 0)
			lex->s[var->z - 1] = add_after_redir(lex->s[var->z - 1], lex->s[var->z + var->i + 1]);
		var->i = var->i + 2;
	}
	if (var->z > 0)
	{	
		ll = fork();
		if (ll == 0)
		{
			if (var->last_pipe == 1)
				dup2(var->fd, STDIN_FILENO);
			if (var->z > 1 && lex->supatok[var->z - 2] == TOKEN_PIPE )
				dup2(var->fd, STDIN_FILENO);
			if (fd_e != -2)
				dup2(fd_e, STDIN_FILENO);
			if (fd_s != -2 && find_cmd_path(var, lex->s[var->z - 1][0]) != 0)
				dup2(fd_s, STDOUT_FILENO);
			executeur(lex->s[var->z - 1], envp, var);
		}
		else
		{
			waitpid(ll, &pip->status2, 0);
			var->z = var->z + 1 + var->i;
			var->last_pipe = 0;
		}
	}
	else 
		var->z = var->z + 1 + var->i;
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
	while (var->z < ft_malloc(lex) - 1)
	{
		if (lex->supatok[var->z] == TOKEN_WORD)
		{
			if (lex->s[var->z + 1] == NULL)
			{
				re = fork();
				if (re == 0)
				{
					if (var->last_pipe == 1)
						dup2(var->fd, STDIN_FILENO);
					executeur_final(lex->s[var->z], envp, var, lex);
				}
				else
				{
					waitpid(re, &pip->status, 0);
					var->last_err_com = WEXITSTATUS(pip->status);
					free_final(lex, pip, var);					
					var->last_pipe = 0;
					return (0);
				}
			}
			else 
			{
				var->z++;
			}
		}
		if(lex->supatok[var->z] == TOKEN_BUILTIN)
		{
			//printf("ayo");
			execve_builtin(lex->s[var->z], envp, var);
		}
		if (lex->supatok[var->z - 1] == TOKEN_PIPE && lex->s[var->z] == NULL)
		{
			var->last_pipe = 1;
			var->z++;
		}
		if (lex->supatok[var->z] == TOKEN_PIPE)
		{
			minipipe(pip, lex, envp, var);	
		}
		if (lex->supatok[var->z] == TOKEN_REDIR_S || lex->supatok[var->z] == TOKEN_REDIR_E
			|| lex->supatok[var->z] == TOKEN_REDIR_S2 || lex->supatok[var->z] == TOKEN_REDIR_E2)
		{
			miniredir_s(lex, var, envp, pip);
			var->c = 0;
			var->i = 0;
		}
	}
	return(0);
}

void process(char **envp, t_var *var)
{
	t_lex lex;
	t_pipe pip;

	var->line = NULL;
	currpath(var);
	find_path(envp, var);
	if (var->last_pipe == 1)
		var->line = readline(">");
	else
		var->line = readline(var->promt);
	var->c = 0;
	if (!var->line)
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	init_tab(&lex, var->line, envp, var); //apres ca la ligne de commande est decoupe dans lex.s1
	tokenizer(&lex);
	lex.s = separate_tok(var, &lex, lex.s);
	lex.s = del_brak(lex.s);
	turbotokenizer(&lex);
	token_builtin(&lex);
	historyset(var, &lex);
	if (parsing_syntax(&lex) == 1)
		exe_s(&lex, var, &pip, envp);
}

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
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	//if (gstruct->is_cmd == 0)
}

void ctrlbs(int sig)
{
	printf("dfqwefwefwe\n");
	fflush(stdout);
	//gstruct->value_of_return = 131;
	
	write(1, "Quit: 3", 7);
	(void)	sig;
}

void ctrld(int sig)
{
	exit(0);
	(void)	sig;
}

void	init_sign(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlbs);
	signal(SIGKILL, ctrld);
}

int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var var;
	//t_lex *lex;
	var.last_err_com = 0;
	var.last_pipe = 0;
	var.check_pipe = 0;
	var.previous_line = NULL;
	init_sign();
	init_termios();
	while (1)
	{
		process(envp, &var); 
	}
	//echo(&var);
}