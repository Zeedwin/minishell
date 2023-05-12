/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:38:12 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/12 10:18:53 by hdelmann         ###   ########.fr       */
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
	var->shell[z] = -1;
}

void	wait_pid(t_var *var, t_pipe *pip)
{
	int	i;

	i = 0;
	while (var->shell[i] != -1)
	{
		waitpid(var->shell[i], &pip->status, 0);
		i++;
	}
	//free(var->shell);
}
