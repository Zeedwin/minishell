/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 05:20:08 by jgirard-          #+#    #+#             */
/*   Updated: 2022/04/09 19:39:34 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*scr;
	unsigned char	*dst;

	i = 0;
	scr = (unsigned char *) s1;
	dst = (unsigned char *) s2;
	while (i != n)
	{
		if (scr[i] != dst[i])
			return (scr[i] - dst[i]);
		i++;
	}
	return (0);
}
