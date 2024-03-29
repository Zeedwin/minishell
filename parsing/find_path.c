/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:01:30 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 19:43:40 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*remo_slash(char *s)
{
	int		i;
	char	*s1;
	int		j;

	s1 = malloc(sizeof(char) * (ft_strlen(s) - 1));
	i = 0;
	j = 0;
	if (s[i] == '.' && s[i + 1] == '/')
	{
		i += 2;
		while (s[i] != '\0')
		{
			s1[j] = s[i];
			i++;
			j++;
		}
		s1[j] = '\0';
		return (s1);
	}
	free(s1);
	return (s);
}

int	c_s(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		i++;
	}
	return (i);
}

void	find_path(char **env, t_var *var)
{
	int		i;
	int		j;
	char	**path2;

	j = 0;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) != 0)
			i++;
		else
		{
			if (ft_strlen(env[i]) > 4)
			{
				path2 = ft_split(&env[i][5], ':');
				var->path = (char **)malloc((c_s(path2) + 1) * sizeof(char *));
				while (path2[j] != NULL)
					(n(), var->path[j] = ft_strjoin(path2[j], "/"), j++);
				(n(), var->path[j] = NULL, free_2(path2), var->nopath = 1);
				i++;
			}
		}
	}
}

int	check_path(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = ft_strlen(s) - 1;
	if (s[i] != '/')
		return (0);
	return (1);
}
