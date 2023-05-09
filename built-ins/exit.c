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

	fflush(stdout);
	exitcd = 0;
	if (lex->s[var->z][1] && ft_num(lex->s[var->z][1]) == 1)
	{
		exitcd = atoi(lex->s[var->z][1]);
		printf("sex\n");
		printf("%d\n", exitcd);
	}
	if (exitcd != 0 && exitcd <= 255)
	{
		g_global.exitcode = exitcd;
		printf("exitcode = %d\n", g_global.exitcode);
		fflush(stdout);
		exit(g_global.exitcode);
	}
	else if (exitcd > 255)
	{
		g_global.exitcode = exitcd % 255;
		exit(g_global.exitcode);
	}
	exit(0);
}
