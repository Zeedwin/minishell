/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:38:12 by jgirard-          #+#    #+#             */
/*   Updated: 2023/04/27 20:38:12 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	exit1(t_var *var, t_lex *lex, t_pipe *pip)
{
	(n(), printf("exit\n"), g_global.bowlingboolean = 1);
	printf("bash : exit: %s: numeric argument required\n",
		lex->s[var->z][1]);
	free_final(lex, pip, var);
	exit(255);
}

void	ft_exit(t_var *var, t_lex *lex, t_pipe *pip)
{
	int	exitcd;

	exitcd = 0;
	if (lex->s[var->z][1] && ft_num(lex->s[var->z][1]) == 1)
		exitcd = atoi(lex->s[var->z][1]);
	else if (lex->s[var->z][1] && ft_num(lex->s[var->z][1]) == 0)
		exit1(var, lex, pip);
	if (exitcd != 0 && exitcd <= 255)
	{
		printf("exit\n");
		free_final(lex, pip, var);
		exit(exitcd);
	}
	else if (exitcd > 255)
	{
		g_global.exitcode = exitcd % 255;
		printf("exit\n");
		free_final(lex, pip, var);
		exit(exitcd);
	}
	printf("exit\n");
	free_final(lex, pip, var);
	exit(0);
}
