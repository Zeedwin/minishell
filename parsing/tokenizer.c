/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:42:56 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 15:08:09 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	test_builtin(char **s)
{
	if (ft_strcmp(s[0], "cd") == 0)
		return (1);
	else if (ft_strcmp(s[0], "env") == 0)
		return (2);
	else if (ft_strcmp(s[0], "export") == 0)
		return (1);
	else if (ft_strcmp(s[0], "echo") == 0)
		return (2);
	else if (ft_strcmp(s[0], "pwd") == 0)
		return (2);
	else if (ft_strcmp(s[0], "unset") == 0)
		return (1);
	else if (ft_strcmp(s[0], "exit") == 0)
		return (2);
	return (0);
}

void	token_builtin(t_lex *lex)
{
	int	i;

	i = 0;
	while (i < ft_malloc(lex) - 2)
	{
		if (lex->supatok[i] == TK_WORD)
		{
			if (test_builtin(lex->s[i]) == 1)
			{
				lex->supatok[i] = TK_BUILTIN;
			}
			else if (test_builtin(lex->s[i]) == 2)
			{
				lex->supatok[i] = TK_BOUT;
			}
		}
		i++;
	}
}
