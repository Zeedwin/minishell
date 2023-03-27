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
		return (1);
	}
	else
	{
	//	printf("bash: cd: %s: No such file or directory\n", file);
	//	printf("l\n");
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
		if(ft_strcmp(s[i], "cd\n"))
		{
		//	printf("%s", s[i]);
			count++;
		}
		//printf("ala%d\n", count);
		k = i;
		if(ft_strcmp(s[i], "cd") && ft_strcmp(s[k + 1], ".."))
		{
			chdir("..");
			return(1);
		}
		//file_input_check(s[i + 1]);
		k = i;
		//printf("%d\n", i);
		if(ft_strcmp(s[i], "cd") == 0 && file_input_check(s[k + 1]))
		{
			k = i;
			printf("%s\n", s[i]);
			chdir(s[k]);
			system("pwd");
			return(1);
		}
		else if (file_input_check(s[k + 1]) == 0)
				{
					if(ft_strcmp(s[k], "cd") != 0)
					{
						printf("error\n");
						return (1);
					}
					printf("bash: cd: %s: No such file or directory\n", s[k]);
					return(1);
				}
		i++;
	}
	//printf("%d\n", count);
	if(count == 1)
	{
	//	printf("%s\n", s[i - 1]);
		chdir(getenv("HOME"));
		system("pwd");
		return(1);
	}
	return(0);
}
/*

	if (ft_strnstr(var->line, "..", 2))
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