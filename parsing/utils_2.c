/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 12:16:59 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/16 13:52:37 by hdelmann         ###   ########.fr       */
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
		if (supatok[i] == TOKEN_PIPE)
		{
			j++;
		}
		i++;
	}
	return (j);
}

int	delimiteur(t_lex *lex, t_var *var, int plus)
{
	char	buffer[BUF_SIZE];
	int		status;
	pid_t	balls;

	var->is_in_heredoc = 1;
	balls = fork();
	if (balls == 0)
		delimiteur2(lex, buffer, plus, var);
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
	if (lex->supatok[var->z - 1] != TOKEN_BUILTIN
		&& lex->supatok[var->z - 1] != TOKEN_BUILTIN_OUTP)
	{
		g_global.is_in_cat = 1;
		var->shell[var->pidnum] = fork();
		if (var->shell[var->pidnum] == 0)
			minipipe1(var, pip, lex);
		else
			minipipe2(var, pip);
	}
	else if (lex->supatok[var->z - 1] == TOKEN_BUILTIN_OUTP)
		minipipe3(var, lex, fdtmp);
	return (1);
}

char	***cpy3truc(t_var *var, t_lex *lex, char ***sf, int decale)
{
	int	i;
	int	j;
	int	k;

	(void)var;
	j = 0;
	i = 0;
	k = 0;
	sf = (char ***)malloc(sizeof(char **) * ft_malloc(lex) + 1);
	while (lex->s1[i])
	{
		if (k == decale)
		{
			sf[k] = NULL;
			k++;
		}
		if (lex->stoken[i] == TOKEN_PIPE || lex->stoken[i] == TOKEN_REDIR_S)
		{
			sf[k] = malloc(sizeof(char *) * 2);
			sf[k][0] = malloc(sizeof(char) * (ft_strlen(lex->s1[i]) + 1));
			sf[k][0] = ft_strcpy(sf[k][0], lex->s1[i]);
			sf[k][1] = NULL;
			k++;
			i++;
		}
		else if (lex->stoken[i] == TOKEN_WORD)
		{
			j = i;
			while (lex->stoken[i] == TOKEN_WORD && lex->s1[i])
				i++;
			sf[k] = malloc(sizeof(char *) * (i - j + 1));
			i = j;
			j = 0;
			while (lex->stoken[i] == TOKEN_WORD && lex->s1[i])
			{
				sf[k][j] = malloc(sizeof(char) * (ft_strlen(lex->s1[i]) + 1));
				sf[k][j] = ft_strcpy(sf[k][j], lex->s1[i]);
				j++;
				i++;
				sf[k][j] = NULL;
			}
			k++;
		}
	}
	sf[k] = NULL;
	return (sf);
}
