/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 12:50:29 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/01 13:54:39 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	point2(char *s)
{
	if (ft_strcmp(s, "\"..\"") == 0 || ft_strcmp(s, "\'..\'") == 0)
		return (0);
	if (ft_strcmp(s, "\".\"") == 0 || ft_strcmp(s, "\'.\'") == 0)
		return (0);
	if (ft_strcmp(s, "\"/\"") == 0 || ft_strcmp(s, "\'/\'") == 0)
		return (0);
	if (ft_strcmp(s, "\"/.\"") == 0 || ft_strcmp(s, "\'/.\'") == 0)
		return (0);
	if (ft_strcmp(s, "\"/..\"") == 0 || ft_strcmp(s, "\'/..\'") == 0)
		return (0);
	if (ft_strcmp(s, "\"/../\"") == 0 || ft_strcmp(s, "\'/../\'") == 0)
		return (0);
	if (ft_strcmp(s, "/") == 0)
		return (0);
	if (check_slash(s) == 1)
		return (0);
	return (1);
}

char	*space_change(char *s)
{
	char	*s1;
	int		i;
	int		j;

	i = 0;
	while (s[i] != '\0' && s[i] == ' ')
	{
		i++;
	}
	s1 = malloc(sizeof(char) * (ft_strlen(s) + 1 - i));
	j = 0;
	while (s[i] != '\0')
	{
		s1[j] = s[i];
		i++;
		j++;
	}
	s1[j] = '\0';
	return (s1);
}

int	check_slash(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != '"' && s[i] != '\'' && s[i] != '/')
			return (0);
		i++;
	}
	return (1);
}

int	check_slash2(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != ' ' && s[i] != '/' && s[i] != '.')
			return (1);
		i++;
	}
	return (0);
}
