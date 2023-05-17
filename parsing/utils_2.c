/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:59 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/17 16:39:23 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	testspace(t_var *var)
{
	int	i;

	i = 0;
	while (var->line[i] != '\0')
	{
		if (var->line[i] != ' ' && var->line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

int	count_pipe(int *supatok, t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (lex->s[i])
	{
		if (supatok[i] == TK_PIPE)
		{
			j++;
		}
		i++;
	}
	return (j);
}

int	delimiteur(t_lex *lex, t_var *var)
{
	char	buffer[BUF_SIZE];
	int		status;
	pid_t	balls;

	var->is_in_heredoc = 1;
	balls = fork();
	if (balls == 0)
		delimiteur2(lex, buffer, var);
	else
		waitpid(balls, &status, 0);
	var->is_in_heredoc = 0;
	return (WEXITSTATUS(status));
}

int	minipipe(t_pipe	*pip, t_lex *lex, t_var *var)
{
	int	fdtmp;

	if (var->c == 0)
	{
		var->c++;
		var->fd = dup(0);
	}
	fdtmp = dup(0);
	dup2(STDOUT_FILENO, fdtmp);
	pipe(pip->tube);
	if (lex->supatok[var->z - 1] != TK_BUILTIN
		&& lex->supatok[var->z - 1] != TK_BUILTIN_OUTP)
	{
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
			minipipe1(var, pip, lex);
		else
			minipipe2(var, pip);
	}
	else if (lex->supatok[var->z - 1] == TK_BUILTIN_OUTP)
		minipipe3(var, lex, fdtmp);
	return (1);
}

char	***cpy3truc(t_var *v, t_lex *lex, char ***sf, int decale)
{
	(norm(), v->p = 0, v->k = 0, v->j = 0,
		sf = (char ***)malloc(sizeof(char **) * ft_malloc(lex)));
	while (lex->s1[v->p])
	{
		if (v->k == decale)
			(norm(), sf[v->k] = NULL, v->k++);
		if (lex->stoken[v->p] == TK_PIPE || lex->stoken[v->p] == TK_REDIR_S)
			(norm(), sf[v->k] = malloc(sizeof(char *) * 2), sf[v->k][0] =
				malloc(sizeof(char) * (ft_strlen(lex->s1[v->p]) + 1)),
				sf[v->k][0] = ft_strcpy(sf[v->k][0], lex->s1[v->p]),
				sf[v->k][1] = NULL, v->k++, v->p++);
		else if (lex->stoken[v->p] == TK_WORD)
		{
			cpy3truc1(v, lex);
			(norm(), sf[v->k] = malloc(sizeof(char *) * (v->p - v->j + 1)),
				v->p = v->j, v->j = 0);
			while (lex->stoken[v->p] == TK_WORD && lex->s1[v->p])
				(norm(), sf[v->k][v->j] = malloc(sizeof(char) * (ft_strlen(lex
					->s1[v->p]) + 1)), sf[v->k][v->j] = ft_strcpy(sf[v->k][v->
					j], lex->s1[v->p]), v->j++, v->p++, sf[v->k][v->j] = NULL);
			v->k++;
		}
	}
	return (sf[v->k] = NULL, sf);
}
