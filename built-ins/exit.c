#include "../includes/shell.h"

void	ft_exit(t_var *var)
{
	if(ft_strnstr(var->line, "exit", ft_strlen(var->line)))
	{
		printf("exit\n");
		exit(1);
	}
}