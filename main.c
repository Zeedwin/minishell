
#include "shell.h"


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

void	cmd1_process(t_var *var, char **envp)
{
	var->cmdpath = find_cmd_path(var, var->cmd1[0]);
	if (var->cmdpath == 0)
		ft_putstr("invalide cmd\n");
	execve(var->cmdpath, var->cmd1, envp);
}


int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var var;
	
	currpath(&var);
	var.line = readline(var.promt);
	//var.line = readline("$>");
	init_cmd(&var);
	find_path(envp, &var);
	cmd1_process(&var, envp);
	
}
//https://www.cs.purdue.edu/homes/grr/SystemsProgrammingBook/Book/Chapter5-WritingYourOwnShell.pdf
//copie ca