/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollar2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:47:41 by jgirard-          #+#    #+#             */
/*   Updated: 2023/06/02 19:43:04 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../includes/shell.h"

void	init_dol(t_ini *in, int i, char *s, int code)
{
	if (code == 0)
	{
		in->j = 0;
		in->k = 0;
		in->o = 0;
		in->res = ft_itoa(i);
		in->sf = malloc(sizeof(char) * (ft_strlen(s) + 1));
	}
	if (code == 1)
	{
		(n(), in->sf[in->o] = s[in->j], in->j++, in->o++);
		while (s[in->j] != '\0' && s[in->j] != '\'')
			(n(), in->sf[in->o] = s[in->j], in->j++, in->o++);
		(n(), in->sf[in->o] = s[in->j], in->j++, in->o++);
	}
}

char	*replace_dol_(char *s, int i, t_ini *in)
{
	init_dol(in, i, s, 0);
	while (s && s[in->j] != '\0')
	{
		if (s[in->j] == '\'')
			init_dol(in, i, s, 1);
		if (s[in->j] == '<' && s[in->j + 1] == '<')
		{
			while ((s[in->j] == ' ' || s[in->j] == '<') && s[in->j] != '\0')
				(n(), in->sf[in->o] = s[in->j], in->j++, in->o++);
			while (s[in->j] != ' ' && s[in->j] != '|'
				&& s[in->j] != '>' && s[in->j] != '<' && s[in->j] != '\0')
				(n(), in->sf[in->o] = s[in->j], in->j++, in->o++);
		}
		if (s[in->j] == '$' && s[in->j + 1] == '?')
		{
			in->sf = realloc(in->sf, ft_strlen(s) + ft_strlen(in->res));
			while (in->res[in->k] != '\0')
				(n(), in->sf[in->o] = in->res[in->k], in->k++, in->o++);
			(n(), in->k = 0, in->j += 2);
		}
		else
			(n(), in->sf[in->o] = s[in->j], in->j++, in->o++);
	}
	return (in->sf[in->o] = '\0', free (in->res), in->sf);
}

char	*del_brak2(char *s)
{
	char	*s1;
	t_ini	p;

	(n(), p.k = ft_strlen(s),
		s1 = malloc(sizeof(char) * (p.k + 1)), s1[0] = '\0', p.i = 0, p.j = 0);
	while (s[p.i] != '\0')
	{
		if (s[p.i] == '\'')
		{
			(n(), p.i++, p.k--, s1 = ft_realloc(s1, (p.k + 1)));
			while (s[p.i] != '\0' && s[p.i] != '\'')
				(n(), s1[p.j] = s[p.i], p.i++, p.j++);
			(n(), s1[p.j] = '\0', p.i++);
		}
		else if (s[p.i] == '"')
		{
			(n(), p.i++, p.k--, s1 = ft_realloc(s1, (p.k + 1)));
			while (s[p.i] != '\0' && s[p.i] != '"')
				(n(), s1[p.j] = s[p.i], p.i++, p.j++);
			(n(), s1[p.j] = '\0', p.i++);
		}
		else
			(n(), s1[p.j] = s[p.i], p.j++, p.i++, s1[p.j] = '\0');
	}
	return (s1[p.j] = '\0', free(s), s1);
}

char	***del_brak(char ***s)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j] != NULL)
		{
			if (check_empty(s[i][j]) == 0)
			{
				free(s[i][j]);
				s[i][j] = NULL;
			}
			else
				s[i][j] = del_brak2(s[i][j]);
			j++;
		}
		i++;
	}
	return (s);
}

int	check_export(char *s)
{
	while (ft_strlen(s) > 5)
	{
		if (ft_strncmp(s, "EXPORT", 6) == 0 || ft_strncmp(s, "export", 6) == 0)
			return (1);
		s++;
	}
	return (0);
}
