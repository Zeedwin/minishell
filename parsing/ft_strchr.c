/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 08:00:47 by jgirard-          #+#    #+#             */
/*   Updated: 2023/01/16 23:11:29 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s [i] && s [i] != (char) c)
	{
		i++;
	}
	if (s [i] == ((char)c))
	{
		return ((char *)(s + i));
	}
	return (NULL);
}
