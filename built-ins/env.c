#include "../includes/shell.h"

void env(char **cpyenv)
{
	int i;

	i = 0;
	while (cpyenv[i])
	{
		printf("%s\n", cpyenv[1]);
		//free(cpyenv[i]);
		i++;
	}
}

char **export(char **cpyenv, char *exported)
{
	int i;
	int len;

	len = 0;
	i = 0;
	while (cpyenv[i])
	{
		i++;
		len++;
	}
	g_global.exp_env = malloc(sizeof(char *) * (len + 2));
	i = 0;
	while (cpyenv[i])
	{
		g_global.exp_env[i] = cpyenv[i];
		//free(cpyenv[i]);
		i++;
	}
	g_global.exp_env[i] = exported;
	g_global.exp_env[i + 1] = NULL;
	//i = 0;
	return(g_global.exp_env);
}