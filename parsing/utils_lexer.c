/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:42:55 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/15 15:50:25 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	error_quote1(char *s, int i, int code)
{
	if (code == 0)
	{
		i++;
		while (s[i] != '\0' && s[i] != '"')
		{
			i++;
			if (s[i] == '\0')
				return (0);
		}
		return (i);
	}
	return (0);
}

int	error_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '"')
		{
			i = error_quote1(s, i, 0);
			if (i == 0)
				return (0);
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
			{
				i++;
				if (s[i] == '\0')
					return (0);
			}
		}
		i++;
	}
	return (1);
}

char	*del_par_com(char *s)
{
	int		i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == '#')
		{
			s = ft_realloc(s, i);
			s[i] = '\0';
		}
		i++;
	}
	return (s);
}

char	*change_tab(char *s)
{
	int	i;

	i = 0;
	while (s && s[i] != '\0')
	{
		if (s[i] == '"')
		{
			i++;
			while (s[i] != '\0' && s[i] != '"')
				i++;
		}
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				i++;
		}
		if (s[i] == '\t')
			s[i] = ' ';
		i++;
	}
	return (s);
}
