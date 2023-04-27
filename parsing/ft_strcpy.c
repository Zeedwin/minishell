/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:04:11 by hdelmann          #+#    #+#             */
/*   Updated: 2022/02/06 21:35:54 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../includes/shell.h"
#include <stdlib.h>

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	equalfinder(char *path)
{
	int	i;
	int	flag;

	flag = 0;
	i = 0;
	while (path[i] && path[i] != '=')
	{
		if (path[i] == '=')
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (-1);
	return (i);
}

char	**ft_strcpy_env(char **cpyenv, char **envp)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (envp[i])
	{
		i++;
		len++;
	}
	i = 0;
	cpyenv = malloc(sizeof(char *) * (len + 1));
	if (!cpyenv)
		return (NULL);
	while (envp[i])
	{
		cpyenv[i] = envp[i];
		i++;
	}
	cpyenv[i] = NULL;
	return (cpyenv);
}

char	**exporting(char **cpyenv, char *exported)
{
	int		i;
	int		len;
	char	**exp_env;
	char	**cpycpy;
	int		j;
	int		check;

	check = 0;
	len = 0;
	i = 0;
	j = 0;
	cpycpy = NULL;
	cpycpy = ft_strcpy_env(cpycpy, cpyenv);
	while (cpycpy[i])
	{
		if ((ft_strncmp(cpycpy[i], exported, equalfinder(cpycpy[i])) == 0))
		{
			len--;
		}
		i++;
		len++;
	}
	if (len < 0)
	{
		free(cpycpy);
		return (NULL);
	}
	exp_env = malloc(sizeof(char *) * (len + 2));
	if (!exp_env)
		return (NULL);
	i = 0;
	while (cpycpy[i])
	{
		if ((ft_strncmp(cpycpy[i], exported, equalfinder(cpycpy[i])) == 0))
		{
			check = 1;
			exp_env[j] = exported;
			j++;
		}
		else
		{
			exp_env[j] = cpycpy[i];
			j++;
		}
		i++;
	}	
	if (check == 1)
	{
		exp_env[j] = NULL;
		free(cpycpy);
		return (exp_env);
	}
	exp_env[j] = exported;
	exp_env[j + 1] = NULL;
	free(cpycpy);
	return (exp_env);
}
