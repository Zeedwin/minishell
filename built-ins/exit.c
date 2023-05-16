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

void	ft_exit(t_var *var, t_lex *lex)
{
	int	exitcd;

	exitcd = 0;
	if (lex->s[var->z][1] && ft_num(lex->s[var->z][1]) == 1)
		exitcd = atoi(lex->s[var->z][1]);
	else if (lex->s[var->z][1] && ft_num(lex->s[var->z][1]) == 0)
	{
		printf("exit\n");
		printf("bash : exit: %s: numeric argument required\n",
			lex->s[var->z][1]);
		exit(2);
	}
	if (exitcd != 0 && exitcd <= 255)
	{
		printf("exit\n");
		exit(exitcd);
	}
	else if (exitcd > 255)
	{
		g_global.exitcode = exitcd % 255;
		printf("exit\n");
		exit(exitcd);
	}
	printf("exit\n");
	exit(0);
}
