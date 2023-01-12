/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: juleng <juleng@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 03:45:39 by jgirard-          #+#    #+#             */
/*   Updated: 2022/09/30 16:12:19 by juleng           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*tmp2;

	if (!lst)
		return ;
	tmp = *lst;
	while (tmp)
	{
		del(tmp->content);
		tmp2 = tmp->next;
		free (tmp);
		tmp = tmp2;
	}
	*lst = NULL;
}
