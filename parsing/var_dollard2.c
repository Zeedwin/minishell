/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:47:41 by jgirard-          #+#    #+#             */
/*   Updated: 2023/05/24 11:51:25 by hdelmann         ###   ########.fr       */
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
		(norm(), in->sf[in->o] = s[in->j], in->j++, in->o++);
		while (s[in->j] != '\'')
			(norm(), in->sf[in->o] = s[in->j], in->j++, in->o++);
		(norm(), in->sf[in->o] = s[in->j], in->j++, in->o++);
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
				(norm(), in->sf[in->o] = s[in->j], in->j++, in->o++);
			while (s[in->j] != ' ' && s[in->j] != '|'
				&& s[in->j] != '>' && s[in->j] != '<' && s[in->j] != '\0')
				(norm(), in->sf[in->o] = s[in->j], in->j++, in->o++);
		}
		if (s[in->j] == '$' && s[in->j + 1] == '?')
		{
			in->sf = realloc(in->sf, ft_strlen(s) + ft_strlen(in->res));
			while (in->res[in->k] != '\0')
				(norm(), in->sf[in->o] = in->res[in->k], in->k++, in->o++);
			(norm(), in->k = 0, in->j += 2);
		}
		else
			(norm(), in->sf[in->o] = s[in->j], in->j++, in->o++);
	}
	return (in->sf[in->o] = '\0', free (in->res), in->sf);
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
		if (s[p.i] == '\'' || s[p.i] == '\"')
		{
			p.i++;
			while (s[p.i] != '\'' && s[p.i] != '\"')
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
