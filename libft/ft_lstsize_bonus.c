/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juleng <juleng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 03:08:53 by jgirard-          #+#    #+#             */
/*   Updated: 2022/09/30 16:12:19 by juleng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	c;

	if (lst == NULL)
		return (0);
	c = 1;
	while (lst->next)
	{
		lst = lst->next;
		c++;
	}
	return (c);
}
