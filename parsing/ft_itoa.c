/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 04:06:08 by hdelmann          #+#    #+#             */
/*   Updated: 2023/03/08 11:25:51 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	get_abs_val(int nb)
{
	if (nb < 0)
		return (-nb);
	return (nb);
}

int	get_len(int nb)
{
	int	len;

	len = 0;
	if (nb <= 0)
		len++;
	while (nb != 0)
	{
		len++;
		nb = nb / 10;
	}
	return (len);
}

char	*ft_itoa(int nb)
{
	char	*res;
	int		len;

	len = get_len(nb);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		return (NULL);
	res[len] = '\0';
	if (nb < 0)
		res[0] = '-';
	else if (nb == 0)
		res[0] = '0';
	while (nb != 0)
	{
		len--;
		res[len] = get_abs_val(nb % 10) + '0';
		nb = nb / 10;
	}
	return (res);
}
