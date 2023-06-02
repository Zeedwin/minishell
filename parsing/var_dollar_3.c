/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollar_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:35:19 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 20:26:03 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*replace_no_dol(char *s, char *s1)
{
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s) - ft_strlen(s1) + 1));
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == s1[0])
		{
			i++;
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '"'
				&& s[i] != '\'' && s[i] != '$')
				i++;
		}
		else
			(n(), s2[j] = s[i], i++, j++);
	}
	s2[j] = '\0';
	if (ft_strlen(s2) == 0)
		return (free(s2), free(s), s = ft_strdup(""), s);
	return (free(s), s2);
}

char	***dolrep_n(t_var	*var, char ***s, t_ini *i, char **env)
{
	if (check_export(s[i->i][i->j]))
		i->p = 1;
	s[i->i][i->j] = dol_replace2(s[i->i][i->j], var, i->p);
	s[i->i][i->j] = dol_replace3(s[i->i][i->j], env, i->p);
	return (s);
}

char	***dol_replace1(char ***s, t_var *var, char **env)
{
	t_ini	i;

	(n(), i.p = 0, i.i = 0);
	while (s != NULL && s[i.i] != NULL)
	{
		i.j = 0;
		while (s[i.i][i.j] != NULL)
		{
			if (check_redir(s[i.i][i.j]) == 1)
			{
				i.i++;
				break ;
			}
			else
				s = dolrep_n(var, s, &i, env);
		i.j++;
		}
		if (s[i.i] == NULL)
			break ;
		i.i++;
	}
	return (s);
}
