/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:48:09 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/16 13:40:03 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	env(char **cpyenv)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	j = 0;
	i = 0;
	while (cpyenv[i])
	{
		j = 0;
		while (cpyenv[i][j])
		{
			if (cpyenv[i][j] == '=')
				flag = 1;
			j++;
		}
		if (flag == 1)
			printf("%s\n", cpyenv[i]);
		flag = 0;
		i++;
	}
}

/*
int check_if_in_env(char **env, char *exported)
{
    int i;

    i = 0;
    while (env[i])
    {

    } 
}
*/

int	if_in_quotes(char *s)
{
	int	i;
	int	counter;

	counter = 0;
	i = 0;
	if (!s)
		return (-1);
	while (s[i])
	{
		if (s[i] == '"' || s[i] == '\'')
			counter++;
		i++;
	}
	if (counter % 2 == 0 && counter != 0)
		return (1);
	return (0);
}

char	**export(char **cpyenv, t_lex *lex, t_var *var, int exp)
{
	int		i;
	int		len;
	char	**exp_env;
	char	**cpycpy;
	int		j;
	int		check;

	(norm(), check = 0, len = 0, i = 0, j = 0, cpycpy = NULL);
	if (lex->s1[2] && lex->s1[1] && if_in_quotes(lex->s1[2]) == 1)
		lex->s[var->z][exp] = ft_strjoin(lex->s[var->z][1], lex->s[var->z][2]);
	else if (!lex->s1[1])
	{
		while (g_global.cpyenv[i])
		{
			printf("declare -x %s\n", g_global.cpyenv[i]);
			i++;
		}
		return (cpyenv);
	}
	(norm(), cpycpy = ft_strcpy_env(cpycpy, cpyenv), i = 0);
	while (cpycpy[i])
	{
		if ((ft_strncmp(cpycpy[i], lex->s[var->z][exp],
				equalfinder(cpycpy[i])) == 0))
			len--;
		i++;
		len++;
	}
	if (len < 0)
		return (free(cpycpy), NULL);
	exp_env = malloc(sizeof(char *) * (len + 2));
	if (!exp_env)
		return (NULL);
	i = 0;
	while (g_global.cpyenv[i])
	{
		if ((ft_strncmp(g_global.cpyenv[i], lex->s[var->z][exp],
				equalfinder(g_global.cpyenv[i])) == 0))
		{
			check = 1;
			exp_env[j] = ft_strdup(lex->s[var->z][exp]);
			j++;
		}
		else
		{
			exp_env[j] = cpycpy[i];
			j++;
		}
		i++;
	}
	if (check == 1)
	{
		return (exp_env[j] = NULL, free(cpycpy), exp_env);
	}
	exp_env[j] = ft_strdup(lex->s[var->z][exp]);
	exp_env[j + 1] = NULL;
	free(cpycpy);
	return (exp_env);
}

char	**unset(char **cpyenvp, char *unsetstr)
{
	t_init	ini;

	(norm(), ini.k = 0, ini.i = 0, ini.c = ft_strlen(unsetstr),
		ini.cpycpy = ft_strcpy_env(cpyenvp, cpyenvp));
	while (ini.cpycpy[ini.i])
	{
		if (ft_strncmp(ini.cpycpy[ini.i], unsetstr, ini.c) == 0)
			ini.k--;
		(norm(), ini.k++, ini.i++);
	}
	if (ini.k < 0)
		return (free(ini.cpycpy), NULL);
	ini.new_envp = (char **)malloc(sizeof(char *) * (ini.k + 2));
	if (!ini.new_envp)
		return (NULL);
	(norm(), ini.i = 0, ini.j = 0);
	while (ini.cpycpy[ini.i])
	{
		if (ft_strncmp(ini.cpycpy[ini.i], unsetstr, ini.c) == 0)
			ini.i++;
		else
			(norm(), ini.new_envp[ini.j] = ini.cpycpy[ini.i], ini.i++, ini.j++);
	}
	ini.new_envp[ini.j] = NULL;
	return (free(ini.cpycpy), ini.new_envp);
}
