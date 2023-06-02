/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:03:37 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 16:13:20 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	free_2(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free(s[i]);
		s[i] = NULL;
		i++;
	}
	free(s);
	s = NULL;
}

void	free_3(char ***s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		free_2(s[i]);
		i++;
	}
	free(s);
	s = NULL;
}

void	free_1(int **s, t_lex *lex)
{
	int	i;
	int	j;

	i = 0;
	j = count_pipe(lex->supatok, lex) + 1;
	while (i < j)
	{
		free(s[i]);
		i++;
	}
}

void	free_final(t_lex *lex, t_pipe *pip, t_var *var)
{
	(void)pip;
	if (lex && lex->s1)
	{
		free_2(lex->s1);
		lex->s1 = NULL;
	}
	if (lex->stoken)
		free(lex->stoken);
	if (lex->supatok)
		free(lex->supatok);
	if (var && var->promt)
		free(var->promt);
	if (var && var->line)
		free(var->line);
	if (var && var->path)
		free_2(var->path);
	if (lex && lex->s)
		free_3(lex->s);
	if (var && var->shell)
		free(var->shell);
}

void	free_final_d(t_pipe *pip, t_var *var)
{
	(void)pip;
	if (var && var->promt)
		free(var->promt);
	if (var && var->path)
		free_2(var->path);
	if (var && g_global.cpyenv)
	{
		free_2(g_global.cpyenv);
	}
}
