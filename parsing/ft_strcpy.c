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
        cpyenv[i] = ft_strdup(envp[i]);
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

    len = 0;
    i = 0;
	cpycpy = NULL;
	cpycpy = ft_strcpy_env(cpycpy, cpyenv);
    while (cpycpy[i])
    {
        i++;
        len++;
    }
    exp_env = malloc(sizeof(char *) * (len + 2));
    if (!exp_env)
        return (NULL);
    i = 0;
    while (cpycpy[i])
    {
        exp_env[i] = cpycpy[i];
        i++;
    }
    exp_env[i] = exported;
    exp_env[i + 1] = NULL;
	free(cpycpy);
    return (exp_env);
}

char **unset(char **cpyenvp, char *unsetstr)
{
    int i;
    int j;
	int k;
    char **new_envp;
	char **cpycpy;

	k = 0;
    i = 0;
	cpycpy = NULL;
	cpycpy = ft_strcpy_env(cpyenvp, cpyenvp);
     while (cpycpy[i])
    {
        if (strncmp(cpycpy[i], unsetstr, strlen(unsetstr)) == 0 &&
            cpycpy[i][strlen(unsetstr)] == '=')
        {
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
        if (strncmp(cpycpy[i], unsetstr, strlen(unsetstr)) == 0 &&
            cpycpy[i][strlen(unsetstr)] == '=')
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
    char **exportedenv = exporting(cpyenvp, "a=sus");
    char **unsettedenv = unset(exportedenv, "a");
    int i = 0;
    while(unsettedenv[i] != NULL)
    {
        printf("> %s\n", unsettedenv[i]);
		free(unsettedenv[i]);
		free(exportedenv[i]);
		free(cpyenvp[i]);
        i++;
    }
	free(unsettedenv);
	free(exportedenv);
	free(cpyenvp);
    return 0;
}