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

char	**ft_strcpy_env(char **cpyenv, char **envp, int deep_copy)
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
		if (!deep_copy)
			cpyenv[i] = envp[i];
		else
			cpyenv[i] = ft_strdup(envp[i]);
		i++;
	}
	cpyenv[i] = NULL;
	return (cpyenv);
}
