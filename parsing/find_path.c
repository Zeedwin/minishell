#include "../includes/shell.h"

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
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			path2 = ft_split(envp[i], ':');
			var->path = (char **)malloc((c_s(path2) + 1) * sizeof(char *));
			while (path2[j] != NULL)
			{
				var->path[j] = ft_strjoin(path2[j], "/");
				j++;
			}
			var->path[j] = NULL;
			free_this(path2);
		}
		i++;
	}	
}

int check_path(char *s)
{
	int i;

	i = ft_strlen(s) - 1;
	if (s[i] != '/')
		return (0);
	return (1);
}

char	*find_cmd_path(t_var *var, char *cmd)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (var->path[i] && check_path(var->path[i]) == 1)
	{
		cmd_path = ft_strjoin(var->path[i], cmd);
		if (access(cmd_path, F_OK | X_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
	return (0);
}


