/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 04:06:08 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/10 14:38:26 by jgirard-         ###   ########.fr       */
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

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_num(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i++;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0 && str[i])
		{
			return (0);
		}
		i++;
	}
	return (1);
}
