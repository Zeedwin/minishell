
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



int main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_var var;
	
	cmd1_process(&var, envp);
	
}
