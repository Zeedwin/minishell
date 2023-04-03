#include "../includes/shell.h"
#include<stdio.h>
#include<unistd.h> 
#include <string.h>

int	file_input_check(char *file)
{
	if(access(file, F_OK) == 0)
		return (1);
	else
		return (0);
}

int	cd(char **s, t_var *var)
{
	int i;
	int k;

	i = 0;
	k = 0;
	if(ft_strcmp(s[i], "cd") && ft_strcmp(s[i + 1], ".."))
	{
		chdir("..");
		return(1);
	}
	k = i;
	while (s[k])
		k++;
   	if(ft_strcmp(s[i], "cd") == 0 && file_input_check(s[i + 1]) == 1)
	{
		chdir(s[i + 1]);
		var->promt = getcwd(var->promt, PATH_MAX);
		return(1);
	}
	else if (k == 1)
	{
		chdir(getenv("HOME"));
		return(1);
	}
	else if(ft_strcmp(s[i], "cd") == 0 && file_input_check(s[i + 1]) != 1 && ft_strcmp(s[i + 1], "cd") == 0)
	{
		printf("bash: cd: %s: No such file or directory\n", s[i + 1]);
		if(ft_strcmp(s[i + 1], "cd") == 0)
			return (1);
		i++;
		return(1);
	}
	return(0);
}
