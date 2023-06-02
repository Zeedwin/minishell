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

int	check_n(char *s)
{
	int	i;

	i = 1;
	if (s[0] != '-')
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo(t_var	*var, t_lex *lex)
{
	int	i;

	i = 1;
	if (lex->s[var->z][1] == NULL && ft_strcmp(lex->s[var->z][0], "echo") == 0)
	{
		printf("\n");
		return (3);
	}
	else if (lex->s[var->z][i] != NULL && check_n(lex->s[var->z][i]) == 1)
	{
		while (lex->s[var->z][i] != NULL && check_n(lex->s[var->z][i]) == 1)
			i++;
		while (lex->s[var->z][i] != NULL)
		{
			printf("%s ", lex->s[var->z][i]);
			i++;
		}
		return (0);
	}
	else if (lex->s[var->z][i] != NULL && check_n(lex->s[var->z][i]) == 0)
	{
		while (lex->s[var->z][i] != NULL)
		{
			printf("%s ", lex->s[var->z][i]);
			i++;
		}
		printf("\n");
		return (0);
	}
	return (0);
}
