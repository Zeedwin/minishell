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

char **unset(char **cpyenvp, char *unsetstr)
{
    int i;
    int j;
	int k;
    int c;
    char **new_envp;
	char **cpycpy;

	k = 0;
    i = 0;
    c = ft_strlen(unsetstr);
	cpycpy = NULL;
	cpycpy = ft_strcpy_env(cpyenvp, cpyenvp);
     while (cpycpy[i])
    {
        if (ft_strncmp(cpycpy[i], unsetstr, c) == 0 &&
            cpycpy[i][c] == '=')
        {
            //free(cpycpy[i]);
            k--;
        }
        k++;
        i++;
    }
    if (k < 0) 
	{
        free(cpycpy);
        return (NULL);
    }
    new_envp = (char **)malloc(sizeof(char *) * (k + 1));
    if (!new_envp)
        return (NULL);
    i = 0;
    j = 0;
    while (cpycpy[i])
    {
        if (ft_strncmp(cpycpy[i], unsetstr, c) == 0 &&
            cpycpy[i][c] == '=')
        {
        	i++;
        	//free(cpycpy[i]);
        }
        else
        {
            new_envp[j] = cpycpy[i];
			i++;
            j++;
        }
    }
    new_envp[j] = NULL;
    free(cpycpy);
    return (new_envp);
}
