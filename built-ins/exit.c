/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 18:05:53 by jgirard-          #+#    #+#             */
/*   Updated: 2023/01/18 18:14:52 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	ft_exit(t_var *var)
{
	if(ft_strnstr(var->line, "exit", ft_strlen(var->line)))
	{
		printf("exit\n");
		exit(1);
	}
}