/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/30 20:04:11 by hdelmann          #+#    #+#             */
/*   Updated: 2022/02/06 21:35:54 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include "../includes/shell.h"
#include <stdlib.h>

char	*ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int equalfinder(char *path)
{
    int i;

    i = 0;
    while(path[i] && path[i] != '=')
    {
        i++;
    }
    return (i);
}

char **ft_strcpy_env(char **cpyenv, char **envp)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (envp[i])
    {
        i++;
        len++;
    }
    i = 0;
    cpyenv = malloc(sizeof(char *) * (len + 1));
    if (!cpyenv)
        return (NULL);
    while (envp[i])
    {
        cpyenv[i] = envp[i];
        i++;
    }
    cpyenv[i] = NULL;
    return (cpyenv);
}

char **exporting(char **cpyenv, char *exported)
{
    int i;
    int len;
    char **exp_env;
	char **cpycpy;
    int c;
    int j;
    int check;

    check = 0;
    len = 0;
    i = 0;
    j = 0;
	cpycpy = NULL;
    c = equalfinder(exported);
    printf("c size = %d\n\n", c);
	cpycpy = ft_strcpy_env(cpycpy, cpyenv);
    while (cpycpy[i])
    {
        if((strncmp(cpycpy[i], exported, equalfinder(cpycpy[i])) == 0))
        {
            len--;
        }
        i++;
        len++;
    }
    printf("%d\n", len);
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
        if((strncmp(cpycpy[i], exported, equalfinder(cpycpy[i])) == 0))
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
        exp_env[j] == NULL;
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
        if (strncmp(cpycpy[i], unsetstr, c) == 0 &&
            cpycpy[i][c] == '=')
        {
            //printf("GAYssysdasd\n");
            k--;
        }
        k++;
        i++;
    }
    if (k < 0) {
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
        if (strncmp(cpycpy[i], unsetstr, c) == 0 &&
            cpycpy[i][c] == '=')
        {
            free(cpycpy[i]);
        }
        else
        {
            new_envp[j] = cpycpy[i];
            j++;
        }
        i++;
    }
    new_envp[j] = NULL;
    free(cpycpy);
    return (new_envp);
}


int main(int ac, char **av, char **envp)
{
    char **cpyenvp = ft_strcpy_env(NULL, envp);
    char **exportedenv = exporting(cpyenvp, "acti=sus");
    char **susenv = exporting(exportedenv, "asa=b");
    char **callenv = exporting(susenv, "aa=e");
    char **calling = unset(callenv, "aa");

    int i = 0;
    while(calling[i] != NULL)
    {
        printf("> %s\n", calling[i]);
        i++;
    }
    free(exportedenv);
    free(susenv);
	free(callenv);
	free(cpyenvp);
    return 0;
}