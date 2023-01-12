/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:28:20 by jgirard-          #+#    #+#             */
/*   Updated: 2022/03/30 04:26:45 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;
	char	*dest;
	char	*source;

	i = 0;
	source = (char *) src;
	dest = (char *) dst;
	while (i < n)
	{
		dest[i] = source[i];
		i++;
	}
	return (dest);
}
