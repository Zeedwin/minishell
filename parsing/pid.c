/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:38:12 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/08 19:41:23 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	creat_pid(t_lex *lex, t_var *var)
{
	int	i;
	int	z;

	i = 0;
	z = 0;
	while (i < ft_malloc(lex) - 1)
	{
		if (lex->supatok[i] != TOKEN_WORD)
			i++;
		else
		{
			if (&lex->s[i][0] == NULL)
				break;
			if (find_cmd_path(var, lex->s[i][0]) == 0)
				i++;
			else
			{
				z++;
				i++;
			}
		}
	}
	var->shell = malloc(sizeof(pid_t) * (z));
}

void	wait_pid(t_var *var, t_pipe *pip)
{
	int	i;

	i = 0;
	while (var->shell[i])
	{
		waitpid(var->shell[i], &pip->status, 0);
		i++;
	}
}
