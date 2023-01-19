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
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stddef.h>

typedef struct s_var {
	char **path;
	char *cmd;
	char **cmd1;
	char *cmdpath;
	char *promt;
	char *line;
	char **line2;
	char *dir;
	pid_t	shell;
}		t_var;

void	free_this(char **tab);
void 	currpath(t_var *var);
int 	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_cmd_path(t_var *var, char *cmd);
void	ft_putstr(char *s);
int		ft_strlen(const char *a);
void	find_path(char **envp, t_var *var);
char	*ft_strcpy(char *dest, char *src);
int 	quotecheker(char *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
void	ft_exit(t_var *var);

//built-ins
int	*cd(t_var *var);

#endif