/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodelmann <hugodelmann@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:48:09 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/25 17:09:25 by hugodelmann      ###   ########.fr       */
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

char	**elp(t_lex *lex, t_var *var, t_init *ine)
{
	while (g_global.cpyenv[ine->i])
	{
		if ((ft_strncmp(g_global.cpyenv[ine->i], lex->s[var->z][ine->exper],
				equalfinder(g_global.cpyenv[ine->i])) == 0))
			(n(), ine->check = 1,
				ine->exp_env[ine->j] = ft_strdup(lex->s[var->z][ine->exper]),
					ine->j++);
		else
			(n(), ine->exp_env[ine->j] = ine->cpycpy[ine->i], ine->j++);
		ine->i++;
	}
	if (ine->check == 1)
		return (ine->exp_env[ine->j] = NULL, free(ine->cpycpy), ine->exp_env);
	return (ine->exp_env[ine->j] = ft_strdup(lex->s[var->z][ine->exper]),
			ine->exp_env[ine->j + 1] = NULL, free(ine->cpycpy), ine->exp_env);
}

char	**export(char **cpyenv, t_lex *lex, t_var *var, int exp)
{
	t_init	ine;

	ine.exper = exp;
	(n(), ine.check = 0, ine.len = 0,
		ine.i = 0, ine.j = 0, ine.cpycpy = NULL);
	if (lex->s1[2] && lex->s1[1] && if_in_quotes(lex->s1[2]) == 1)
		lex->s[var->z][exp] = ft_strjoin(lex->s[var->z][1], lex->s[var->z][2]);
	else if (!lex->s1[1])
		return (exportprint(cpyenv));
	(n(), ine.cpycpy = ft_strcpy_env(ine.cpycpy, cpyenv), ine.i = 0);
	while (ine.cpycpy[ine.i])
	{
		if ((ft_strncmp(ine.cpycpy[ine.i], lex->s[var->z][exp],
				equalfinder(ine.cpycpy[ine.i])) == 0))
			ine.len--;
		(n(), ine.i++, ine.len++);
	}
	if (ine.len < 0)
		return (free(ine.cpycpy), NULL);
	ine.exp_env = malloc(sizeof(char *) * (ine.len + 2));
	if (!ine.exp_env)
		return (NULL);
	ine.i = 0;
	return (elp(lex, var, &ine));
}

char	**unset(char **cpyenvp, char *unsetstr)
{
	t_init	ini;

	(n(), ini.k = 0, ini.i = 0, ini.c = ft_strlen(unsetstr),
		ini.cpycpy = ft_strcpy_env(cpyenvp, cpyenvp));
	while (ini.cpycpy[ini.i])
	{
		if (ft_strncmp(ini.cpycpy[ini.i], unsetstr, ini.c) == 0)
			ini.k--;
		(n(), ini.k++, ini.i++);
	}
	if (ini.k < 0)
		return (free(ini.cpycpy), NULL);
	ini.new_envp = (char **)malloc(sizeof(char *) * (ini.k + 2));
	if (!ini.new_envp)
		return (NULL);
	(n(), ini.i = 0, ini.j = 0);
	while (ini.cpycpy[ini.i])
	{
		if (ft_strncmp(ini.cpycpy[ini.i], unsetstr, ini.c) == 0)
			ini.i++;
		else
			(n(), ini.new_envp[ini.j] = ini.cpycpy[ini.i], ini.i++, ini.j++);
	}
	ini.new_envp[ini.j] = NULL;
	return (free(ini.cpycpy), ini.new_envp);
}
