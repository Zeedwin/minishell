/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 17:24:38 by jgirard-          #+#    #+#             */
/*   Updated: 2022/05/27 21:04:54 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *restrict dst, const char *restrict src,
		size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!src || !dst)
	{
		return (0);
	}
	if (dstsize == 0)
	{
		return (ft_strlen(src));
	}
	while (src[i] != '\0' && i < dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i])
		i++;
	return (i);
}
// int main()
// {
	// char src[] = "coucou";
	// char dest[10]; memset(dest, 'A', 10);
	// char stdsrc[] = "coucou";
	// char stddest[10]; memset(stddest, 'A', 10);
	// printf("%zu\n", ft_strlcpy(dest, src, 0));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcpy(stddest, stdsrc, 0));
	// printf("%s\n", stddest);
	// printf("%zu\n", ft_strlcpy(dest, src, 1));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcpy(stddest, stdsrc, 1));
	// printf("%s\n", stddest);
	// printf("%zu\n", ft_strlcpy(dest, src, 2));
	// printf("%s\n", dest);
	// printf("%zu\n", strlcpy(stddest, stdsrc, 2));
	// printf("%s\n", stddest);
// }
// 