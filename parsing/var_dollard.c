/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollard.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:43:50 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/17 12:49:08 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*appl_ching(int i, char *sf, char *so, int o)
{
	while (so[i] != '$')
	{
		if (so[i] == '\'')
		{
			i++;
			while (so[i] != '\'')
				i++;
			i++;
		}
		if (so[i] == '<' && so[i + 1] == '<')
		{
			i += 2;
			while (so[i] == ' ' && so[i] != '\0')
				i++;
			while (so[i] != ' ' && so[i] != '|' && so[i] != '>'
				&& so[i] != '<' && so[i] != '\0')
				i++;
		}
		(norm(), sf[i] = so[i], i++);
	}
	while (so[o] != '\0')
		(norm(), sf[i] = so[o], o++, i++);
	return (sf[i] = '\0', sf);
}

char	*appl_chang(char *so, char *sc, int k, int o)
{
	int		i;
	int		j;
	char	*sf;

	(norm(), i = 0, j = 0, sf = malloc(sizeof(char)
			* (ft_strlen(so) + ft_strlen(sc) - (o - k) + 1)));
	while (i < k)
		(norm(), sf[i] = so[i], i++);
	if (sc != NULL)
	{
		while (sc[j] != '\0')
			(norm(), sf[i] = sc[j], i++, j++);
		while (so[o] != '\0')
		{
			(norm(), sf[i] = so[o], o++, i++);
		}
		sf[i] = '\0';
		return (sf);
	}
	else
	{
		return (appl_ching(i, sf, so, o));
	}
}

char	*change_value(char *s, char **env)
{
	int		i;
	int		j;
	int		o;
	char	*s2;

	o = ft_strlen(s);
	i = 0;
	s2 = NULL;
	while (env[i])
	{
		j = 0;
		if (ft_strncmp(env[i], s, ft_strlen(s)) == 0)
		{
			s2 = malloc(sizeof(char) * (ft_strlen(env[i]) - ft_strlen(s) + 1));
			while (g_global.cpyenv[i][o] != '\0')
			{
				s2[j] = env[i][o];
				j++;
				o++;
			}
			s2[j] = '\0';
		}
		i++;
	}
	return (s2);
}

char	*replace_dol(char *s, char **env)
{
	int		i;
	int		j;
	int		o;
	char	*sf;
	char	*s1;

	(norm(), i = 0, j = 0, o = 0);
	while (s[i] != '$' && s[i] != '\0')
		i++;
	(norm(), sf = malloc(sizeof(char) * (i + 1)), i = 0);
	while (s[i] != '$' && s[i] != '\0')
		(norm(), sf[j] = s[i], i++, j++);
	(norm(), sf[j] = '\0', i++,
		s1 = malloc(sizeof(char) * (ft_strlen(s) - i + 2)));
	while (s[i] != '\0')
		(norm(), s1[o] = s[i], o++, i++);
	(norm(), s1[o] = '\0', s1 = change_value(s1, env), i = 0);
	if (s1 != NULL)
	{
		sf = ft_realloc(sf, (ft_strlen(s1) + j + 1));
		while (s1[i] != '\0')
			(norm(), sf[j] = s1[i], i++, j++);
		sf[j] = '\0';
	}
	return (sf);
}

char	*dollars_ch(char *s, char **env)
{
	t_init	p;

	(norm(), p.i = 0, p.k = 0, p.j = 0);
	while (p.i <= ft_strlen(s) && s[p.i] != '\0')
	{
		if (s[p.i] == '\'')
		{
			p.i++;
			while (s[p.i] != '\'')
				p.i++;
			p.i++;
		}
		if (s[p.i] == '<' && s[p.i + 1] == '<')
		{
			p.i += 2;
			while (s[p.i] == ' ' && s[p.i] != '\0')
				p.i++;
			while (s[p.i] != ' ' && s[p.i] != '|'
				&& s[p.i] != '>' && s[p.i] != '<' && s[p.i] != '\0')
				p.i++;
		}
		if (s[p.i] == '$')
		{
			p.o = 0;
			while (s[p.i] != ' ' && p.i > 0 && s[p.i] != '"')
				p.i--;
			(norm(), p.k = p.i, p.i++, p.j = p.i);
			while (s[p.i] != ' ' && s[p.i] != '\0' && s[p.i] != '"')
				p.i++;
			p.s2 = malloc(sizeof(char) * (p.i - p.j + 2));
			while (p.j < p.i)
				(norm(), p.s2[p.o] = s[p.j], p.o++, p.j++);
			(norm(), p.s2[p.o] = '=', p.o++, p.s2[p.o] = '\0',
				p.s2 = replace_dol(p.s2, env),
				s = appl_chang(s, p.s2, p.k + 1, p.i));
		}
		p.i++;
	}
	return (s);
}
