/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_path1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 13:55:09 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/17 14:55:18 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*find_cmd_path2(char *cmd, char *cmd_path, char *buf)
{
	cmd = remo_slash(cmd);
	cmd_path = ft_strjoin(getcwd(buf, PATH_MAX), "/");
	cmd_path = ft_strjoin(cmd_path, cmd);
	if (access(cmd_path, F_OK | X_OK) == 0)
		return (cmd_path);
	else
	{
		printf("mamongus\n");
		return (0);
	}
	free(cmd_path);
	return (0);
}

char	*free_return(char *cmd_path, char *path)
{
	free(path);
	return (cmd_path);
}

char	*find_cmd_path1(t_var *var, char *cmd, char *path, char *cmd_path)
{
	int		i;

	i = 0;
	while (var->path[i] && check_path(var->path[i]) == 1)
	{
		cmd_path = ft_strjoin_free(var->path[i], cmd, 0);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_return(cmd_path, path));
		free(cmd_path);
		i++;
	}
	i = 0;
	cmd = ft_strjoin("..", cmd);
	while (var->path[i] && check_path(var->path[i]) == 1)
	{
		cmd_path = ft_strjoin(var->path[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (free_return(cmd_path, path));
		free(cmd_path);
		i++;
	}
	free (path);
	free (cmd);
	return (0);
}

char	*find_cmd_path(t_var *var, char *cmd)
{
	char	*cmd_path;
	char	buf[PATH_MAX];
	char	*path;
	char	*path0;

	path0 = ft_strjoin_free(getcwd(buf, PATH_MAX), "/", 0);
	path = ft_strjoin_free(path0, cmd, 1);
	cmd_path = NULL;
	if ((cmd[0] == '.' && cmd[1] == '.' && cmd[2] == '/')
		|| (cmd[0] == 'r' && cmd[1] == '\0'));
	else if (access(path, F_OK | X_OK) == 0)
		return (path);
	else if (cmd[0] == '.' && cmd[1] == '/')
		return (find_cmd_path2(cmd, cmd_path, buf));
	else if (var->nopath == 1)
		return (find_cmd_path1(var, cmd, path, cmd_path));
	free(path);
	return (0);
}
