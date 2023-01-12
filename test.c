

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <unistd.h>        // getcwd
#include <limits.h>



void currpath(t_var s) 
{
   
    if ( getcwd( s.promt, PATH_MAX ) == NULL ) {
        fprintf( stderr, "Cannot get current working directory path\n" );
        if ( errno == ERANGE ) {
            fprintf( stderr, "Buffer size is too small.\n" );
        }
        exit( EXIT_FAILURE );
	}
    printf( "Current working directory: %s\n", s.promt);
}