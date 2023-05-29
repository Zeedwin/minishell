/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:48:04 by jgirard-          #+#    #+#             */
/*   Updated: 2023/04/27 20:48:04 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# define BUF_SIZE 10
# define PATH_MAX 4096

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
# include <ctype.h>
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
	char	**cmd;
	int		pipe_out;
	int		pipe_in;
}	t_cmd;

typedef struct s_pipe {
	int		**pipe;
	int		cmd1;
	int		cmd2;
	int		prevpipe;
	pid_t	pid;
	int		status;
	int		status1;
	int		status2;
	int		tube[2];
}	t_pipe;

enum {
	TK_WORD,
	TK_PIPE,
	TK_REDIR_S,
	TK_REDIR_E,
	TK_REDIR_S2,
	TK_REDIR_E2,
	TK_CMD,
	TK_DOLLAR,
	TK_BUILTIN,
	TK_BOUT,
	TK_FIN,
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
	int		count_wait;
	int		check_after_redir;
	char	**path;
	char	**cpyenv;
	char	*cmd;
	int		fd_base;
	char	**cmd1;
	int		counti;
	int		countj;
	int		fd_hdoc;
	int		lacontedetagrandmere;
	char	*promt;
	char	*line;
	int		memo;
	char	**line2;
	char	*dir;
	char	*echo;
	char	**exp_env;
	int		last_pipe;
	char	*previous_line;
	int		did_fail;
	int		check_pipe;
	pid_t	*shell;
	int		fd_e;
	int		fd_s;
	int		fail_dir;
	int		pidnum;
	int		c;
	int		z;
	int		j;
	int		p;
	int		k;
	int		bowlingboolean;
	int		nopath;
	int		i;
	int		is_in_heredoc;
	int		is_in_cat;
	int		fd;
	int		last_err_com;
	int		exitcode;
}	t_var;

extern t_var	g_global;

typedef struct s_lex
{
	int		x;
	char	**s1;
	int		ii;
	char	*ss;
	char	***s;
	int		*stoken;
	int		*supatok;
	int		c;
	int		y;
}			t_lex;

typedef struct s_init
{
	char	**cpycpy;
	char	**new_envp;
	int		i;
	int		j;
	int		k;
	int		c;
	int		o;
	char	**exp_env;
	int		len;
	int		check;
	int		exper;
	char	*s2;
}			t_init;

typedef struct s_ini
{
	char	*sf;
	char	*res;
	int		j;
	int		o;
	int		k;
	int		i;
	int		p;
	int		l;
	int		m;
}	t_ini;

char	*replace_dol_env(char *s, int i);
char	**ft_realloc2(char **map, int i);
char	*dol_replace2(char *s, t_var *var);
char	*dol_replace3(char *s, char **env);
char	*ft_replace_dol_in(char *s, char *res);
int		check_export(char *s);
char	**exportprint(char	**cpyenv);
int		check_redir(char *s);
void	ctrlc(int sig);
void	ctrld(int sig);
void	init_sign(void);
void	ctrlbs(int sig);
int		check_eq2(char *str);
int		incr_i(t_lex *lex, t_var *var);
int		break_p(t_lex *lex, t_var *var);
int		minipipe(t_pipe	*pip, t_lex *lex, t_var *var);
char	***cpy3thing(t_var *var, t_lex *lex, char ***sf, int decale);
void	init_termios(void);
void	rl_replace_line(const char *text, int clear_undo);
char	*replace_dol_(char *s, int i, t_ini *ini);
void	n(void);
char	*ft_realloc(char *map, int i);
void	execute_final(char **s, char **env, t_var *var, t_lex *lex);
void	process(t_var *var);
int		ft_malloc(t_lex *lex);
void	turbotokenizer2(t_lex *lex);
int		minipipe(t_pipe	*pip, t_lex *lex, t_var *var);
void	init_tab(t_lex *lex, char *s, char **envp, t_var *var);
char	*ft_strdup(const char *src);
void	free_this(char **tab);
void	currpath(t_var *var);
void	token_builtin(t_lex *lex);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*find_cmd_path(t_var *var, char *cmd);
void	ft_putstr(char *s);
int		ft_strlen(const char *a);
int		lexer6(t_lex *l, int i, int code);
char	**add_if_after(char **s1);
char	**add_after_redir(char **s1, char **s2);
void	miniredir_s5(t_lex	*lex, t_var *var, t_pipe *pip);
int		ft_strlen2(const char *a);
void	find_path(char **env, t_var *var);
int		miniredir_s4(t_lex *lex, t_var *var);
char	*ft_strcpy(char *dest, char *src);
int		quotecheker(char *s, char c);
int		miniredir_s7(t_lex *lex, t_var *var, t_pipe *pip);
int		miniredir_s8(t_lex *lex, t_var *var, int fdtmp, t_pipe *pip);
char	*ft_strtrim(char const *s1, char const *set);
size_t	ft_strlcpy(char *restrict dst,
			const char *restrict src, size_t dstsize);
char	***cpytrichar(char ***s, int decale);
char	*replace_no_dol(char *s, char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strstrlen(char **s);
char	*ft_strchr(const char *s, int c);
char	*ft_strnstr(const char *haystack, const char *needle, int len);
int		ft_strcmp(char *s1, char *s2);
char	*ft_strstr(char *str, char *to_find);
char	*del_backn(char *s);
char	*dollars_ch(char *s1, char **env);
int		ft_malloc2(t_lex *lex);
char	*ft_itoa(int nb);
char	***del_brak(char ***s);
void	execve_builtin(char **s, t_var *var, t_lex *lex, int i);
int		ft_isdigit(int c);
int		error_quote(char *s, t_ini *i);
void	cpy3thing1(t_var *v, t_lex *lex);
char	*del_pos(char *s, int pos);
int		pro(t_lex *lex, t_var *var, t_pipe *pip);
void	execute_final22(char *cmdpath, char **s, char **env);
int		check_empty(char *s);
char	***dol_replace1(char ***s, t_var *var, char **env);
void	parent_pro(t_lex *lex, t_var *var, t_pipe *pip);
char	*change_tab(char *s);
void	process_init(t_lex *lex, t_var *var);
int		error_quote2(char *s, int i, int code);
int		point(char *s);
char	*space(char *s);
int		ft_num(char *str);
void	i_lexer(char *s, t_lex *lex, int code);
char	*del_par_com(char *s);
int		turbotokenizer1(t_lex *lex, int i);
void	*ft_calloc(size_t count, size_t size);
void	ft_bzero(void *s, size_t n);
char	*ft_substr_free(char *s, unsigned int start, size_t len);
char	*ft_strdup_free(char *src);
char	*ft_strjoin_free(char *s1, char *s2, int freeable);
size_t	ft_strlcpy(char *restrict dst, const char *restrict src,
			size_t dstsize);
char	***separate_tok(t_var *var, t_lex *lex, char ***s);
void	tokenizer(t_lex *lex);
void	minipipe3(t_var *var, t_lex *lex, int fdtmp, t_pipe *pip);
void	minilife(t_var	*var);
void	minilife2(t_var	*var, t_lex	*lex);
void	minilife3(t_var	*var);
void	microredir(t_var *var);
void	turbotokenizer(t_lex *lex);
void	execute(char **s, char **env, t_var *var);
void	free_final(t_lex *lex, t_pipe *pip, t_var *var);
void	free_2(char **s);
int		exe_s(t_lex *lex, t_var *var, t_pipe *pip);
int		count_pipe(int *supatok, t_lex *lex);
int		miniredir_s(t_lex *lex, t_var *var, t_pipe *pip);
int		miniredir_s2(t_lex *lex, t_var *var, char **env, t_pipe *pip);
int		parsing_syntax(t_lex *lex);
int		test_builtin(char **s);
int		equalfinder(char *path);
void	break_p2(t_lex *lex, char *buffer, t_var *var);
void	minipipe2(t_var *var, t_pipe *pip);
void	minipipe1(t_var *var, t_pipe *pip, t_lex *lex);
int		count(char *s, t_var *var);
void	wait_pid(t_var *var, t_pipe *pip);
void	creat_pid(t_lex *lex, t_var *var);
char	*remo_slash(char *s);
int		check_path(char *s);
int		lexer1(t_lex *lex);
void	free_3(char ***s);
void	init_sign(void);
char	*lexeur2(t_lex *lex, int i);
int		lexer4(t_lex *l, int i);
int		lexer3(t_lex *l, int i, int code);
int		lexer5(t_lex *l, int i);

//built-ins
char	*minidoll_ch(char *s, t_init p, char **env);
int		cd(char **s, t_var *var);
char	**export(char **cpyenv, t_lex *lex, t_var *var, int i);
char	**unset(char **cpyenvp, char *unsetstr);
int		exec_builtin_out(char **s, t_var *var, t_lex *lex, t_pipe *pip);
int		echo(t_var	*var, t_lex *lex);
void	pwd(void);
char	**ft_strcpy_env(char **cpyenv, char **envp);
void	env(char **cpyenv);
void	ft_exit(t_var *var, t_lex *lex, t_pipe *pip);

#endif