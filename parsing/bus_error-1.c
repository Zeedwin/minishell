/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bus_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstojilj <mstojilj@student.42nice.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/10 15:35:11 by mstojilj          #+#    #+#             */
/*   Updated: 2023/04/10 15:37:37 by mstojilj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char	*ft_strrev(char *s)
{
	int		i = 0;
	int		j = strlen(s);
	char	c;

	while (i < j)
	{
		c = s[i];
		s[i] = s[j];
		s[j] = c;
		i++;
		j--;
	}
	return (s);
}

int	main(void)
{
	char	*s = "milan";

	ft_strrev(s);
}