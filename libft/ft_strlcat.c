/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:32:22 by jgirard-          #+#    #+#             */
/*   Updated: 2023/01/12 14:11:30 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, int s)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dst[i])
		i++;
	if (s < ft_strlen(dst))
	{
		while (src[j])
			j++;
		return (s + j);
	}
	while (s > 0 && i < s - 1 && src[j])
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	while (src[j++])
	{
		i++;
	}
	return (i);
}

/*
int	main(void)
 {
	char	s1[18];
	char	s2[18];

	ft_strlcat(s1, "Julen dqwdqwddqd", 18);
	strlcat(s2, "Julen dqwdqwddqd", 18);
	 printf("1 = %s\n", s1);
	 printf("2 = %s\n", s2);
	
}
*/