#include "../includes/shell.h"
#include<stdio.h>
#include<unistd.h> 
#include <string.h>

int	file_input_check(char *file)
{
	//printf("w");
	//fflush(stdout);
	if(access(file, F_OK) == 0)
	{
		printf("w");
		return (1);
	}
	else
	{
		printf("l");
		return (0);
	}
}

int	cd(char **s)
{
	int i;
	int count;
	int k;

	i = 1;
	count = 0;
	k = 0;
	while(s[i])
	{
		//fflush(stdout);
		if(ft_strcmp(s[i], "cd"))
			count++;
		k = i;
		/*if(ft_strcmp(s[i], "cd") && ft_strcmp(s[k + 1], ".."))
		{
			chdir("..");
			return(1);
		}*/
		//printf("%s", s[i + 1]);
		//file_input_check(s[i + 1]);
		k = i;
		printf("%d", i);
		if(ft_strcmp(s[i], "cd") && file_input_check(s[i + 1]))
		{
			printf("%s", s[i]);
			chdir(s[i + 1]);
			//system("pwd");
			return(1);
		}
		i++;
	}
	if(count == 1)
	{
		chdir(getenv("HOME"));
		return(1);
	}
	return(0);
}

/*	if (ft_strnstr(var->line, "..", 2))
	{
	}
	else if ((ft_strncmp(var->line, "cd", 2) == 0) && ft_strlen(var->line) == 2)
	{
		chdir(getenv("HOME"));
	}
	else if(ft_strncmp(var->line, "cd ", 3) == 0)
	{
		var->dir = ft_strtrim(var->line, "cd ");
		chdir(var->dir);
	}*/