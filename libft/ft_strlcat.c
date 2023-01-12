/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 15:32:22 by jgirard-          #+#    #+#             */
/*   Updated: 2022/03/29 18:31:32 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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

size_t	ft_strlcat(char *dst, const char *src, size_t s)
{
	size_t	i;
	size_t	j;

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