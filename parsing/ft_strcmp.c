/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 20:26:53 by hdelmann          #+#    #+#             */
/*   Updated: 2023/03/06 13:44:24 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char *del_backn(char *s)
{
	int i;
	char *s1;

	s1 = malloc(ft_strlen(s) * sizeof(char));
	i = 0;
	while (s[i] != '\n' && s[i] != '\0')
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;
	i = 0;
	while (s1[i] == s2[i] && (s1[i] != '\0' || s2[i] != '\0') && (s1[i] != '\n' || s2[i] != '\n'))
	{
		i++;
	}
	return (s1[i] - s2[i]);
}
