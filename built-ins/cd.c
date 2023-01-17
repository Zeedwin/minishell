#include "../includes/shell.h"
#include<stdio.h>
#include<unistd.h> 
#include <string.h>

int	*cd(t_var *var)
{
	char *usr;

	usr = getenv("USER");
	if (ft_strnstr(var->line, "..", 2))
	{
		chdir("..");
	}
	else if ((strncmp(var->line, "cd", 2) == 0) && ft_strlen(var->line) == 2)
	{
		//printf("dasdasdas\n");
		chdir(ft_strjoin("/Users/", usr));
	}
	else if(strncmp(var->line, "cd ", 3) == 0)
	{
		var->dir = ft_strtrim(var->line, "cd ");
		chdir(var->dir);
	}
	return(0);
}