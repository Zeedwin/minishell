/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pid.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugodelmann <hugodelmann@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:38:12 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/25 11:33:19 by hugodelmann      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	creat_pid(t_lex *lex, t_var *var)
{
	int		i;
	char	*s;

	i = 0;
	while (i < ft_malloc(lex) - 1)
	{
		if (lex->supatok[i] != TK_WORD)
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
				var->count_wait++;
				i++;
			}
			free(s);
		}
	}
	var->shell = ft_calloc((var->count_wait + 1), sizeof(pid_t));
}

void	wait_pid(t_var *var, t_pipe *pip)
{
	int	i;

	i = 0;
	while (i <= var->count_wait)
	{
		waitpid(var->shell[i], &pip->status, 0);
		i++;
	}
}
