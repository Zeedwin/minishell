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
	int	i;

	if (lex->s[var->z][1] == NULL && ft_strcmp(lex->s[var->z][0], "echo") == 0)
	{
		printf("\n");
		return (3);
	}
	if (ft_strcmp(lex->s[var->z][1], "-n") == 0 && lex->s[var->z][2] != NULL)
	{
		i = 1;
		while (ft_strcmp(lex->s[var->z][i], "-n") == 0 || ft_strcmp(lex->s[var->z][i], "n") == 0)
			i++;
		while (lex->s[var->z][i])
		{
			printf("%s", lex->s[var->z][i]);
			if (i != 2)
				printf(" ");
			i++;
		}
		return (2);
	}
	if (ft_strcmp(lex->s[var->z][0], "echo") == 0 && lex->s[var->z][1] != NULL)
	{
		i = 1;
		while (lex->s[var->z][i])
		{
			printf("%s", lex->s[var->z][i]);
			printf(" ");
			i++;
		}
		printf("\n");
		return (1);
	}
	return (4);
}
