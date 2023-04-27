/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:38:23 by jgirard-          #+#    #+#             */
/*   Updated: 2023/04/27 20:38:23 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	echo(t_var	*var, t_lex *lex)
{
	if (lex->s[var->z][1] == NULL && ft_strcmp(lex->s[var->z][0], "echo") == 0)
	{
		printf("\n");
		return (3);
	}
	if (lex->s[var->z][2] == NULL && ft_strcmp(lex->s[var->z][1], "-n") != 0)
	{
		printf("%s\n", lex->s[var->z][1]);
		return (1);
	}
	if (ft_strcmp(lex->s[var->z][1], "-n") == 0 && lex->s[var->z][2] != NULL)
	{
		printf("%s", lex->s[var->z][2]);
		return (2);
	}
	return (4);
}
