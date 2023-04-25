#include "../includes/shell.h"

void creat_pid(t_lex *lex, t_var *var)
{
	int i;
	int z;

	i = 0;
	z = 0;
	while (i < ft_malloc(lex) - 1)
	{
		if(lex->supatok[i] != TOKEN_WORD)
			i++;
		else
			if(find_cmd_path(var, lex->s[i][0]) == 0)
				i++;
			else
			{
				z++;
				i++;
			}
	}
	fflush(stdout);
	var->shell = malloc(sizeof(pid_t) * (z));
}

void wait_pid(t_var * var, t_pipe *pip)
{
	int i;

	i = 0;
	while(var->shell[i])
	{
		//printf("et de %d", i);
		//printf(" .  pid = %d\n", var->shell[i]);
		waitpid(var->shell[i], &pip->status, 0);
		i++;
	}
}