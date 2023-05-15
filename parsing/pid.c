/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:38:12 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/15 11:28:07 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	creat_pid(t_lex *lex, t_var *var)
{
	int	i;
	char *s;
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
				break ;
			s = find_cmd_path(var, &lex->s1[i][0]);
			if (s == 0)
				i++;
			else
			{
				z++;
				i++;
			}
			free(s);
		}
	}
	var->shell = malloc(sizeof(pid_t) * (z + 1));
	var->count_wait = z + 1;
	var->shell[z] = -2;
}

void	wait_pid(t_var *var, t_pipe *pip)
{
	int	i;

	i = 0;
	while (var->shell[i] != -2 && i < var->count_wait)
	{
		waitpid(var->shell[i], &pip->status, 0);
		i++;
	}
	//free(var->shell);
}
