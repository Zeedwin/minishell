#ifndef SHELL_H
# define SHELL_H

#define BUF_SIZE 10

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
# include <sys/types.h>
# include <signal.h>
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
# include <termios.h>
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
	int status1;
	int status2;
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
	TOKEN_BUILTIN,
	TOKEN_BUILTIN_OUTP,
};

enum {
	CD,
	ECHOO,
	EXPORT,
	PWD,
	UNSET,
	ENV,
	EXIT,
};

typedef struct s_var {
	char **path;
	char **cpyenv;
	char *cmd;
	char **cmd1;
	char *cmdpath;
	char *promt;
	char *line;
	char **line2;
	char *dir;
	char *echo;
	char **exp_env;
	int last_pipe;
	char *previous_line;
	int check_pipe;
	pid_t	shell;
	int c;
	int z;
	int i;
	int is_in_heredoc;
	int fd;
	int last_err_com;
}		t_var;

extern t_var g_global;

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


char *replace_dol_(char *s, int i);
char	*ft_realloc(char *map, int i);
void executeur_final(char **s, char **envp, t_var *var, t_lex *lex);
void process(char **envp, t_var *var);
int ft_malloc(t_lex *lex);
int	minipipe(t_pipe	*pip, t_lex *lex, char **envp, t_var *var);
void init_tab(t_lex *lex, char *s, char **envp, t_var *var);
char	*ft_strdup(const char *src);
void	free_this(char **tab);
void 	currpath(t_var *var);
void token_builtin(t_lex *lex);
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
int	ft_strcmp(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
char *del_backn(char *s);
char *dollars_ch(char *s1, char **envp);
char	*ft_itoa(int nb);
char ***del_brak(char ***s);
int execve_builtin(char **s, char **envp, t_var *var, t_lex *lex);

//token	*ft_lstnew(char **content);
size_t	ft_strlcpy(char *restrict dst, const char *restrict src, size_t dstsize);
void	echo(t_var	*var);
void tokenizer(t_lex *lex);
char ***separate_tok(t_var *var, t_lex *lex, char ***s);
void	turbotokenizer(t_lex *lex);
void executeur(char **s, char **envp, t_var *var);
void free_final(t_lex *lex, t_pipe *pip, t_var *var);
void free_2(char **s);
int exe_s(t_lex *lex, t_var *var, t_pipe *pip, char **envp);
int count_pipe(int *supatok, t_lex *lex);
int miniredir_s(t_lex *lex, t_var *var, char **envp, t_pipe *pip);
int miniredir_s2(t_lex *lex, t_var *var, char **envp, t_pipe *pip);
int parsing_syntax(t_lex *lex);
int test_builtin(char **s);
int equalfinder(char *path);



//built-ins
int		cd(char **s, t_var *var);
void 	pwd();
int		exec_builtin_out(char **s);
char	**ft_strcpy_env(char **cpyenv, char **envp);
void 	env(char **cpyenv);
char 	**export(char **cpyenv, char *exported);

#endif