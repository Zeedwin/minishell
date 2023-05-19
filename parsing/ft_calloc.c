/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 07:53:37 by jgirard-          #+#    #+#             */
/*   Updated: 2023/05/19 10:23:24 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	printf("jaime pas les = %ld jaime pas les = %ld\n", count, size);
	printf("ethan raciste central %ld\n", count * size);
	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}
