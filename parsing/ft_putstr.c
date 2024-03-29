/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 21:01:37 by jgirard-          #+#    #+#             */
/*   Updated: 2023/04/27 21:01:37 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../includes/shell.h"

void	ft_putstr(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] != '\0')
	{
		write (1, &s[i], 1);
		i++;
	}
}
