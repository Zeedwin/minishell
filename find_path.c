#include "shell.h"

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

void	find_path(char **envp, t_var *var)
{
	int		i;
	int		j;
	char	**path2;

	j = 0;
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 1)
		{
			path2 = ft_split(envp[i], ':');
			var->path = (char **)malloc((c_s(path2) + 1) * sizeof(char *));
			while (path2[j])
			{
				var->path[j] = ft_strjoin(path2[j], "/");
				j++;
			}
			free_this(path2);
		}
		i++;
	}	
}

char	*find_cmd_path(t_var *var, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (var->path[i])
	{
		cmd_path = ft_strjoin(var->path[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
		{
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	return (0);
}


