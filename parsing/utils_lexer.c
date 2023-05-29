/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:42:55 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/29 12:32:17 by jgirard-         ###   ########.fr       */
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

int	error_quote2(char *s, int i, int code)
{
	if (code == 0)
	{
		i++;
		while (s[i] != '\0' && s[i] != '\'')
		{
			i++;
			if (s[i] == '\0')
				return (0);
		}
		return (i);
	}
	return (0);
}

int	error_quote(char *s, t_ini *i)
{
	(n(), i->p = 0, i->l = 0, i->m = 0);
	while (s[i->p] != '\0')
	{
		if (s[i->p] == '"')
		{
			(n(), i->m++, i->p = error_quote1(s, i->p, 0));
			if (i->p == 0)
				return (0);
			if (s[i->p] == '"')
				i->m++;
		}
		if (s[i->p] == '\'')
		{
			(n(), i->l++, i->p = error_quote2(s, i->p, 0));
			if (i->p == 0)
				return (0);
			if (s[i->p] == '\'')
				i->l++;
		}
		i->p++;
	}
	if (i->m % 2 != 0 || i->l % 2 != 0)
		return (0);
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
