/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:48:09 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/01 23:29:40 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

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

char	**exportprint(char	**cpyenv)
{
	int	i;

	i = -1;
	while (g_global.cpyenv[++i])
		printf("declare -x %s\n", g_global.cpyenv[i]);
	return (cpyenv);
}

char	**elp(t_lex *lex, t_var *var, t_init *ine, char	**cpyenv)
{
	while (g_global.cpyenv[ine->i])
	{
		if ((ft_strncmp(g_global.cpyenv[ine->i], lex->s[var->z][ine->exper],
				equalfinder(g_global.cpyenv[ine->i])) == 0))
			(n(), ine->check = 1,
				ine->exp_env[ine->j] = ft_strdup(lex->s[var->z][ine->exper]),
					ine->j++);
		else
			(n(), ine->exp_env[ine->j] = cpyenv[ine->i], ine->j++);
		ine->i++;
	}
	if (ine->check == 1)
		return (ine->exp_env[ine->j] = NULL, ine->exp_env);
	return (ine->exp_env[ine->j] = ft_strdup(lex->s[var->z][ine->exper]),
			ine->exp_env[ine->j + 1] = NULL, ine->exp_env);
}

char	**export(char **cpyenv, t_lex *lex, t_var *var, int exp)
{
	t_init	ine;

	if (!lex->s[var->z][1])
		return (exportprint(cpyenv));
	ine.exper = exp;
	(n(), ine.check = 0, ine.len = 0,
		ine.i = 0, ine.j = 0);
	while (cpyenv[ine.i])
	{
		if ((ft_strncmp(cpyenv[ine.i], lex->s[var->z][exp],
				equalfinder(cpyenv[ine.i])) == 0))
			ine.len--;
		(n(), ine.i++, ine.len++);
	}
	if (ine.len < 0)
		return (free_2(cpyenv), NULL);
	ine.exp_env = malloc(sizeof(char *) * (ine.len + 2));
	if (!ine.exp_env)
		return (NULL);
	ine.i = 0;
	return (elp(lex, var, &ine, cpyenv));
}

int	expsize(char **cpyenv, char	*var, char *lex)
{
	while ( condition )
	{
		code 
	}
	
}

char	**export_la_renaissance(char **cpyenv, t_var *var, t_lex *lex)
{
	int	i;
	int k;
	int size;

	i = 0;
	k = 1;
	size = 0;
	
	while (cpyenv[i])
		i++;
	while (lex->s[var->z][k])
		k++;
	size = k + i;
	k = 1;
	while (lex->s[var->z][k])
	{
		if (check_eq2(lex->s[var->z][k]) != 0)
			size--;
		k++;
	}
	while (cpyenv[i])
	{
		if (ft_strcmp(cpyenv, ))
		i++;
	}
	
	var->lrn = malloc(sizeof(char *) * (size + 1));
	
}

char	**unset(char **cpyenvp, char *unsetstr)
{
	t_init	ini;

	if (!unsetstr[0])
		return (g_global.cpyenv);
	(n(), ini.k = 0, ini.i = 0, ini.c = ft_strlen(unsetstr),
		ini.cpycpy = ft_strcpy_env(cpyenvp, cpyenvp, 0));
	while (ini.cpycpy[ini.i])
	{
		if (ft_strncmp(ini.cpycpy[ini.i], unsetstr, ini.c) == 0)
			ini.k--;
		(n(), ini.k++, ini.i++);
	}
	if (ini.k < 0)
		return (free(ini.cpycpy), NULL);
	ini.new_envp = (char **)malloc(sizeof(char *) * (ini.k + 2));
	(n(), ini.i = 0, ini.j = 0);
	while (ini.cpycpy[ini.i])
	{
		if (ft_strncmp(ini.cpycpy[ini.i], unsetstr, ini.c) == 0)
			ini.i++;
		else
			(n(), ini.new_envp[ini.j] = ini.cpycpy[ini.i], ini.i++, ini.j++);
	}
	return (ini.new_envp[ini.j] = NULL, free(ini.cpycpy), ini.new_envp);
}
