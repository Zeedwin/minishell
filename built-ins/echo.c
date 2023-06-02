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
	if (s == NULL)
		return (0);
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

void	writing_echo(t_var *var, t_lex *lex, int i)
{
	write(1, lex->s[var->z - 1][i], ft_strlen(lex->s[var->z - 1][i]));
	write(1, " ", 1);
}

int	echo(t_var	*var, t_lex *lex)
{
	int	i;

	i = 1;
	if (lex->s[var->z - 1][1] == NULL &&
		ft_strcmp(lex->s[var->z - 1][0], "echo") == 0)
		printf("\n");
	else if (lex->s[var->z - 1][i] != NULL
		&& check_n(lex->s[var->z - 1][i]) == 1)
	{
		while (lex->s[var->z - 1][i] != NULL
			&& check_n(lex->s[var->z - 1][i]) == 1)
			i++;
		while (lex->s[var->z - 1][i] != NULL)
			(n(), writing_echo(var, lex, i), i++);
	}
	else if (lex->s[var->z - 1][i] != NULL
		&& check_n(lex->s[var->z - 1][i]) == 0)
	{
		while (lex->s[var->z - 1][i] != NULL)
			(n(), printf("%s ", lex->s[var->z - 1][i]), i++);
		printf("\n");
	}
	return (0);
}

void	init_sign(void)
{
	signal(SIGINT, ctrlc);
	signal(SIGQUIT, ctrlbs);
}
