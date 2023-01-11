
#include "shell.h"
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>

void	free_this(char **tab)
{
	int	x;

	x = 0;
	while (tab[x] != NULL)
	{
		free(tab[x]);
		x++;
	}
	free(tab);
}

int check_endcmd(char a)
{
	if (a == '|')
		return (0);
	if (a == '<')
		return (0);
	if (a == '>')
		return (0);
	if (a == '\0')
		return (0);
	return (1);
}

void init_cmd(t_var *var)
{
	int i;

	i = 0;
	while (check_endcmd(var->line[i]) == 1)
	{
		var->cmd[i] = var->line[i];
		i++;
	}
	var->cmd1 = ft_split(var->cmd, ' ');
}


int main(int ac, char **av, char **envp)
{
	
	char *ar;
	t_var var;
	
	currpath(var);
	var.line = readline(var.promt);
	
	
}

// "ls -la jg uy uy | > www"

/*int main(int ac, char **av, char **envp)
{
    t_var	s;

	(void)av;
	(void)ac;
	(void)envp;
	/*arg = readline(s.promt);
	s.line = ft_split(arg, ' ')
    if ( getcwd( s.promt, PATH_MAX ) == NULL ) {
        fprintf( stderr, "Cannot get current working directory path\n" );
        if ( errno == ERANGE ) {
            fprintf( stderr, "Buffer size is too small.\n" );
        }
        exit( EXIT_FAILURE );
    }

    printf( "Current working directory: %s\n", s.promt);
    
    return EXIT_SUCCESS;
}*/