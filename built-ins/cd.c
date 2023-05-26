/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:46:23 by hdelmann          #+#    #+#             */
/*   Updated: 2023/04/27 10:46:23 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
#include<stdio.h>
#include<unistd.h> 
#include <string.h>

int	file_input_check(char *file)
{
	int	fi;

	fi = open(file, O_RDONLY, O_RDWR);
	if (access(file, F_OK) == 0)
	{
		if (fi == -1)
			printf("Permission denied\n");
		return (1);
	}
	else
	{
		return (0);
	}
}

void	n(void)
{
}

int	cd(char **s, t_var *var)
{
	int		i;
	int		k;

	(n(), i = 0, k = -1);
	if (ft_strcmp(s[i], "cd") && ft_strcmp(s[i + 1], ".."))
		return (chdir(".."), 1);
	while (s[k])
		k++;
	if (k == 1)
		return (chdir(getenv("HOME")), 1);
	else if (ft_strcmp(s[i], "cd") == 0 && file_input_check(s[i + 1]) == 1)
	{
		chdir(s[i + 1]);
		var->promt = getcwd(var->promt, PATH_MAX);
		return (1);
	}
	else if (ft_strcmp(s[i], "cd") == 0 && file_input_check(s[i + 1]) != 1)
	{
		printf("bash: cd: %s: No such file or directory\n", s[i + 1]);
		if (ft_strcmp(s[i + 1], "cd") == 0)
			return (1);
		i++;
		return (1);
	}
	return (0);
}
