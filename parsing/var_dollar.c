/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:43:50 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 20:30:30 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*change_value(char *s, char **env, t_var *var)
{
	int		i;
	int		j;
	int		o;
	char	*s2;

	(n(), (void)var, o = ft_strlen(s), i = 0, s2 = NULL);
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

char	*replace_dol_env2(char *s, char **env)
{
	char	*s1;
	int		i;
	char	*s2;
	int		j;
	int		k;

	(n(), i = 0, s1 = ft_strjoin(s, "="), j = ft_strlen(s1), k = 0);
	while (env[i])
	{
		if (ft_strncmp(env[i], s1, ft_strlen(s1)) == 0)
		{
			s2 = malloc(sizeof(char) * (ft_strlen(env[i]) - ft_strlen(s1) + 1));
			while (env[i][j] != '\0')
			{
				s2[k] = env[i][j];
				k++;
				j++;
			}
			s2[k] = '\0';
			free(s1);
			return (s2);
		}
		i++;
	}
	return (s2 = malloc(sizeof(char)), s2[0] = '\0', free(s1), s2);
}

char	*replace_dol_fi(char *s, char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;
	int		k;

	(n(), i = 0, k = 0, j = 0,
		s3 = malloc(sizeof(char) * (ft_strlen(s)
				- ft_strlen(s1) + ft_strlen(s2) + 1)));
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == s1[0] && j == 0 && ft_strlen(s2) != 0)
		{
			i++;
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '"'
				&& s[i] != '\'' && s[i] != '$')
				i++;
			while (s2[j] != '\0')
				(n(), s3[k] = s2[j], k++, j++);
		}
		else
			(n(), s3[k] = s[i], k++, i++);
	}
	return (free(s), s3[k] = '\0', s3);
}

char	*dolr_n(char *s1, char *s2, char *s)
{
	if (ft_strlen(s2) != 0)
		s = replace_dol_fi(s, s1, s2);
	else
		s = replace_no_dol(s, s1);
	return (s);
}
