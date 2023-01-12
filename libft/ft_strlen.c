/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:28:13 by jgirard-          #+#    #+#             */
/*   Updated: 2022/03/24 23:13:43 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"libft.h"
#include <stdio.h>

size_t	ft_strlen(const char	*str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i ++;
	return (i);
}
