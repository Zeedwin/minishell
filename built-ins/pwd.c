#include "../includes/shell.h"

void pwd()
{
	char promt1[PATH_MAX];
	char *pwd;

	pwd = getcwd(promt1, PATH_MAX);
	printf("%s\n", pwd);
}