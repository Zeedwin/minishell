/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollar_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:35:19 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/29 15:15:17 by jgirard-         ###   ########.fr       */
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

char	***dol_replace1(char ***s, t_var *var, char **env)
{
	t_ini	i;

	i.i = 0;
	while (s != NULL && s[i.i] != NULL)
	{
		i.j = 0;
		while (s[i.i][i.j] != NULL)
		{
			if (check_redir(s[i.i][i.j]) == 1 || check_export(s[i.i][i.j]))
			{
				i.i++;
				break ;
			}
			else
			{
				s[i.i][i.j] = dol_replace2(s[i.i][i.j], var);
				s[i.i][i.j] = dol_replace3(s[i.i][i.j], env);
			}
			i.j++;
		}
		if (s[i.i] == NULL)
			break ;
		i.i++;
	}
	return (s);
}
