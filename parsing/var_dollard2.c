/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:47:41 by jgirard-          #+#    #+#             */
/*   Updated: 2023/05/19 14:25:38 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../includes/shell.h"

char	*replace_dol_(char *s, int i)
{
	t_init	ma;

	(norm(), ma.j = 0, ma.k = 0, ma.o = 0, ma.res = ft_itoa(i),
		ma.sf = malloc(sizeof(char) * (ft_strlen(s) + 1)));
	while (s && s[ma.j] != '\0')
	{
		if (s[ma.j] == '\'')
			ma.sf = idowanttopaychildsupport(ma, s);
		if (s[ma.j] == '<' && s[ma.j + 1] == '<')
			ma.sf = idontwanttopaychildsupport(ma, s);
		if (s[ma.j] == '$' && s[ma.j + 1] == '?')
		{
			ma.sf = realloc(ma.sf, ft_strlen(s) + ft_strlen(ma.res));
			while (ma.res[ma.k] != '\0')
				(norm(), ma.sf[ma.o] = ma.res[ma.k], ma.k++, ma.o++);
			(norm(), ma.k = 0, ma.j += 2);
		}
		else
			(norm(), ma.sf[ma.o] = s[ma.j], ma.j++, ma.o++);
	}
	return (ma.sf[ma.o] = '\0', free (ma.res), ma.sf);
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
