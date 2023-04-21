#include "../includes/shell.h"

void env(char **cpyenv)
{
	int i;

	i = 0;
	while (cpyenv[i])
	{
		printf("%s\n", cpyenv[i]);
		//free(cpyenv[i]);
		i++;
	}
}

char **export(char **cpyenv, char *exported)
{
    int i;
    int len;
    char **exp_env;
	char **cpycpy;

    int j;
    int check;

    check = 0;
    len = 0;
    i = 0;
    j = 0;
	cpycpy = NULL;
    //c = equalfinder(exported);
    //printf("c size = %d\n\n", c);
	cpycpy = ft_strcpy_env(cpycpy, cpyenv);
    while (cpycpy[i])
    {
        if((ft_strncmp(cpycpy[i], exported, equalfinder(cpycpy[i])) == 0))
        {
            len--;
        }
        i++;
        len++;
    }
  //  printf("%d\n", len);
    if (len < 0) {
        free(cpycpy);
        return (NULL);
    }
    exp_env = malloc(sizeof(char *) * (len + 2));
    if (!exp_env)
        return (NULL);
    i = 0;
    while (cpycpy[i])
    {
        if((ft_strncmp(cpycpy[i], exported, equalfinder(cpycpy[i])) == 0))
        {
            check = 1;
            exp_env[j] = exported;
            j++;
        }
        else
        {
            exp_env[j] = cpycpy[i];
            j++;
        }
        i++;
    }
    if(check == 1)
    {
        //printf("%s\n", exp_env[j]);
        exp_env[j] = NULL;
        free(cpycpy);
        return(exp_env);
    }
    exp_env[j] = exported;
    exp_env[j + 1] = NULL;
	free(cpycpy);
    //printf("\n\n\n\n");
    return (exp_env);
}