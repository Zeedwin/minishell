#ifndef SHELL_H
# define SHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stddef.h>
# include <stdint.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include <limits.h>
#include <errno.h>

typedef struct s_var {
	char **path;
	char *cmd;
	char **cmd1;
	char *cmdpath;
	char promt[PATH_MAX];
	char **line;
}		t_var;

void	free_this(char **tab);
void 	currpath(t_var s);


#endif