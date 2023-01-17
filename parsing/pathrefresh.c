

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/shell.h"
#include <unistd.h>        // getcwd
#include <limits.h>



void currpath(t_var *var) 
{
	char promt1[PATH_MAX];
	int i;

    if ( getcwd(promt1, PATH_MAX ) == NULL ) {
        fprintf( stderr, "Cannot get current working directory path\n" );
        if ( errno == ERANGE ) {
            fprintf( stderr, "Buffer size is too small.\n" );
        }
        exit( EXIT_FAILURE );
	}
	var->promt = malloc((ft_strlen(promt1) + 2) * sizeof(char));
	i = ft_strlen(promt1);
	var->promt = ft_strcpy(var->promt, promt1);
	var->promt[i] = '>';
	var->promt[i + 1] = '\0';
	var->promt = ft_strjoin("\033[1;36m➜\033[1;32m", var->promt);
	var->promt = ft_strjoin(var->promt, "\033[0m");
    //printf( "%s\n", s.promt);
}