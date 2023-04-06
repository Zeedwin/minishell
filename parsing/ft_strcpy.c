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

char	**ft_strcpy_env(char **cpyenv, char **envp)
{
	int i;
	int	len;

	i = 2;
	len = 0;
	while (envp[i])
	{
		i++;
		len++;
	}
	i = 2;
	cpyenv = malloc(sizeof(char *) * (len + 1));
	while (envp[i] != NULL)
	{
		cpyenv[i] = envp[i];
		i++;
	}
	cpyenv[i] = NULL;
	i = 2;
	return(&cpyenv[i]);
}