#include "../includes/shell.h"

void env(char **cpyenv)
{
	int i;

	i = 0;
	while (cpyenv[i])
	{
		printf("%s\n", cpyenv[i]);
		i++;
	}
}

int if_in_quotes(char *s)
{
    int i;
    int counter;

    counter = 0;
    i = 0;
    if(!s)
        return(-1);
    while (s[i])
    {
        if(s[i] == '"')
            counter++;
        i++;
    }
    if(counter % 2 == 0 && counter != 0)
        return(1);
    return(0);
}

char **export(char **cpyenv, t_lex *lex, t_var *var)
{
    int i;
    int len;
    char **exp_env;
	char **cpycpy;
    int k;
    int j;
    int check;
    int flag;

    flag = 0;
    k = 1;
    check = 0;
    len = 0;
    i = 0;
    j = 0;
	cpycpy = NULL;
    if(lex->s1[2] && lex->s1[1] && if_in_quotes(lex->s1[2]) == 1)
    {
       lex->s[var->z][1] = ft_strjoin(lex->s[var->z][1], lex->s[var->z][2]);
    }
    else if(!lex->s1[1])
    {
        while (cpyenv[i])
        {
            printf("declare -x %s\n", cpyenv[i]);
            i++;
        }
        return(cpyenv);
    }
    i = 0;
    while (lex->s[var->z][k][i])
    {
        if(lex->s[var->z][k][i] == '=')
            flag = 1;
        i++;
    }
    i = 0;
    if (flag != 1)
    return(cpyenv);
    
	cpycpy = ft_strcpy_env(cpycpy, cpyenv);
    while (cpycpy[i])
    {
        if((ft_strncmp(cpycpy[i], lex->s[var->z][1], equalfinder(cpycpy[i])) == 0))
        {
            len--;
        }
        i++;
        len++;
    }
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
        if((ft_strncmp(cpycpy[i], lex->s[var->z][1], equalfinder(cpycpy[i])) == 0))
        {
            check = 1;
            exp_env[j] = lex->s[var->z][1];
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
        exp_env[j] = NULL;
        free(cpycpy);
        return(exp_env);
    }
    exp_env[j] = lex->s[var->z][1];
    exp_env[j + 1] = NULL;
	free(cpycpy);
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