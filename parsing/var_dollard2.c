/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:47:41 by jgirard-          #+#    #+#             */
/*   Updated: 2023/05/19 13:46:45 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../includes/shell.h"

char	*replace_dol_(char *s, int i)
{
	char	*sf;
	char	*res;
	int		j;
	int		o;
	int		k;

	(norm(), j = 0, k = 0, o = 0, res = ft_itoa(i),
		sf = malloc(sizeof(char) * (ft_strlen(s) + 1)));
	while (s && s[j] != '\0')
	{
		if (s[j] == '\'')
		{
			(norm(), sf[o] = s[j], j++, o++);
			while (s[j] != '\'')
				(norm(), sf[o] = s[j], j++, o++);
			(norm(), sf[o] = s[j], j++, o++);
		}
		if (s[j] == '<' && s[j + 1] == '<')
		{
			while ((s[j] == ' ' || s[j] == '<') && s[j] != '\0')
				(norm(), sf[o] = s[j], j++, o++);
			while (s[j] != ' ' && s[j] != '|'
				&& s[j] != '>' && s[j] != '<' && s[j] != '\0')
				(norm(), sf[o] = s[j], j++, o++);
		}
		if (s[j] == '$' && s[j + 1] == '?')
		{
			sf = realloc(sf, ft_strlen(s) + ft_strlen(res));
			while (res[k] != '\0')
				(norm(), sf[o] = res[k], k++, o++);
			(norm(), k = 0, j += 2);
		}
		else
			(norm(), sf[o] = s[j], j++, o++);
	}
	return (sf[o] = '\0', free (res), sf);
}

char	***del_brak(char ***s)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j] != NULL)
		{
			if (s[i][j][0] == '"' || s[i][j][0] == '\'')
			{
				k = 1;
				s[i][j] = ft_realloc(s[i][j], ft_strlen(s[i][j]) - 2);
				while (k < ft_strlen(s[i][j]) - 1)
					(norm(), s[i][j][k - 1] = s[i][j][k], k++);
				s[i][j][k - 1] = '\0';
			}
			j++;
		}
		i++;
	}
	return (s);
}

int	ft_minishellstolemywife(char *s, t_init p)
{
	p.i += 2;
	while (s[p.i] == ' ' && s[p.i] != '\0')
		p.i++;
	while (s[p.i] != ' ' && s[p.i] != '|'
		&& s[p.i] != '>' && s[p.i] != '<' && s[p.i] != '\0')
		p.i++;
	return (p.i);
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
			p.i = ft_minishellstolemywife(s, p);
		if (s[p.i] == '$')
			s = minidoll_ch(s, p, env);
		p.i++;
	}
	return (s);
}
