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
# include <sys/wait.h>
# include <signal.h>

typedef struct cmd {
	char **cmd;
	int	 pipe_out;
	int  pipe_in;
}	cmd_t;

typedef struct s_pipe {
	int **pipe;
	int cmd1;
	int cmd2;
	int prevpipe;
	pid_t pid;
	int status;
	int tube[2];
}	t_pipe;

enum {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_S,
	TOKEN_REDIR_E,
	TOKEN_REDIR_S2,
	TOKEN_REDIR_E2,
	TOKEN_CMD,
	TOKEN_DOLLAR,
};

typedef struct s_var {
	char **path;
	char *cmd;
	char **cmd1;
	char *cmdpath;
	char *promt;
	char *line;
	char **line2;
	char *dir;
	char *echo;
	pid_t	shell;
	int c;
	int z;
	int i;
}		t_var;



typedef struct s_lex
{
	int x;
	char **s1;
	char ***s;
	int *stoken;
	int *supatok;
	int c;
	int y;
	int rap;
}			t_lex;

void	rl_replace_line (const char *text, int clear_undo);

int ft_malloc(t_lex *lex);
int	minipipe(t_pipe	*pip, t_lex *lex, char **envp, t_var *var);
void init_tab(t_lex *lex, char *s);
char	*ft_strdup(const char *src);
void	free_this(char **tab);
void 	currpath(t_var *var);
int 	ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_cmd_path(t_var *var, char *cmd);
void	ft_putstr(char *s);
int		ft_strlen(const char *a);
int		ft_strlen2(const char *a);
void	find_path(char **envp, t_var *var);
char	*ft_strcpy(char *dest, char *src);
int 	quotecheker(char *s, char c);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
void	ft_exit(t_var *var);
//token	*ft_lstnew(char **content);
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize);
void	echo(t_var	*var);
void tokenizer(t_lex *lex);
char ***separate_tok(t_var *var, t_lex *lex, char ***s);
void	turbotokenizer(t_lex *lex);
void executeur(char **s, char **envp, t_var *var);
void free_final(t_lex *lex, t_pipe *pip, t_var *var);
void free_2(char **s);
void exe_s(t_lex *lex, t_var *var, t_pipe *pip, char **envp);
int count_pipe(int *supatok, t_lex *lex);
int miniredir_s(t_lex *lex, t_var *var, char **envp, t_pipe *pip);

//built-ins
int	*cd(t_var *var);

#endif