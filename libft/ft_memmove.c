/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:28:24 by jgirard-          #+#    #+#             */
/*   Updated: 2022/03/30 04:00:28 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{	
	size_t	i;
	char	*dst2;
	char	*src2;
	char	*temp;

	dst2 = (char *)dst;
	src2 = (char *)src;
	temp = malloc(sizeof(char) * len);
	i = 0;
	while (i < len)
	{
		temp[i] = src2[i];
		i++;
	}
	i = 0;
	while (i < len)
	{
		dst2[i] = temp[i];
		i++;
	}
	free (temp);
	return (dst2);
}
