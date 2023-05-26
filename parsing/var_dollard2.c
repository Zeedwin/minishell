/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollard2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodelmann <hugodelmann@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/17 12:47:41 by jgirard-          #+#    #+#             */
/*   Updated: 2023/05/26 09:05:41 by hugodelmann      ###   ########.fr       */
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
	int i;
	int j;
	int k;
	char *s1;

	k = ft_strlen(s);
	s1 = malloc(sizeof(char) * (k + 1));
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			k--;
			s1 = ft_realloc(s1, (k + 1));
			while (s[i] != '\0' && s[i] != '\'')
			{
				s1[j] = s[i];
				i++;
				j++;
			}
			i++;
		}
		else if (s[i] == '"')
		{
			i++;
			k--;
			s1 = ft_realloc(s1, (k + 1));
			while (s[i] != '\0' && s[i] != '"')
			{
				s1[j] = s[i];
				i++;
				j++;
			}
			i++;
		}
		else
		{
			s1[j] = s[i];
			j++;
			i++;
		}
	}
	s1[j] = '\0';
	return (s1);
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
			s[i][j] = del_brak2(s[i][j]);
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

	(n(), p.i = 0, p.k = 0, p.j = 0);
	while (p.i <= ft_strlen(s) && s[p.i] != '\0')
	{
		if (s[p.i] == '\'' || s[p.i] == '\"')
		{
			p.i++;
			while (s[p.i] != '\0' && s[p.i] != '\'' && s[p.i] != '\"')
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
