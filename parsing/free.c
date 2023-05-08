/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:03:37 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/08 03:18:45 by jgirard-         ###   ########.fr       */
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
		i++;
	}
	free(s);
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
	if(lex->s1)
		free_2(lex->s1);
	//free(lex->stoken);
	//free(lex->supatok);
//	free_3(lex->s);
//	free(var->line);
	//free(var->previous_line);
	free(var->promt);
	if(var->line)
		free(var->line);
	if (var->path)
		free_2(var->path);
}
