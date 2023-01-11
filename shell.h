#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# include <errno.h>
# include <stdio.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_var {
	char **path;
	char *cmd;
	char **cmd1;
	char *cmdpath;
	char *promt;
	char *line;
}		t_var;

void	free_this(char **tab);
void 	currpath(t_var *var);
int		ft_strncmp(char *s1, char *s2, int n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_cmd_path(t_var *var, char *cmd);
void	ft_putstr(char *s);
int		ft_strlen(const char *a);
void	find_path(char **envp, t_var *var);
char	*ft_strcpy(char *dest, char *src);


#endif