/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:01:30 by hdelmann          #+#    #+#             */
/*   Updated: 2023/04/27 10:01:30 by hdelmann         ###   ########.fr       */
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
	}
	return (s1);
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
		{
			i++;
		}
		else
		{
			path2 = ft_split(env[i], ':');
			var->path = (char **)malloc((c_s(path2) + 1) * sizeof(char *));
			while (path2[j] != NULL)
			{
				var->path[j] = ft_strjoin(path2[j], "/");
				j++;
			}
			var->path[j] = NULL;
			free_2(path2);
			var->nopath = 1;
			i++;
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

char	*find_cmd_path(t_var *var, char *cmd)
{
	int		i;
	char	*cmd_path;
	char	buf[PATH_MAX];
	char	*path;
	char	*path0;

	path0 = ft_strjoin(getcwd(buf, PATH_MAX), "/");
	path = ft_strjoin(path0, cmd);
	free(path0);
	i = 0;
	if (cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
	{
		return (0);
	}
	if (access(path, F_OK | X_OK) == 0)
	{
		free(path);
		return (path);
	}
	if (cmd[0] == '.' && cmd[1] == '/')
	{
		cmd = remo_slash(cmd);
		cmd_path = ft_strjoin(getcwd(buf, PATH_MAX), "/");
		cmd_path = ft_strjoin(cmd_path, cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	if (var->nopath == 1)
	{
		while (var->path[i] && check_path(var->path[i]) == 1)
		{
			cmd_path = ft_strjoin(var->path[i], cmd);
			if (access(cmd_path, F_OK | X_OK) == 0)
				return (cmd_path);
			//free(path);
			free(cmd_path);
			i++;
		}
		i = 0;
		cmd = ft_strjoin("..", cmd);
		while (var->path[i] && check_path(var->path[i]) == 1)
		{
			cmd_path = ft_strjoin(var->path[i], cmd);
			if (access(cmd_path, F_OK | X_OK) == 0)
				return (cmd_path);
			free(cmd_path);
			i++;
		}
		//free(path);
	}
	free(cmd);
	free(path);
	return (0);
}
