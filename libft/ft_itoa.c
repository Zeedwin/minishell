/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:47:03 by jgirard-          #+#    #+#             */
/*   Updated: 2022/04/02 20:08:14 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char		buf[12];
	int			i;
	const int	neg = n < 0;

	if (!neg)
		n = -n;
	i = 12;
	buf[--i] = '\0';
	while (1)
	{
		buf[--i] = '0' - n % 10;
		n /= 10;
		if (n == 0)
		{
			if (neg)
				buf[--i] = '-';
			return (ft_strdup(buf + i));
		}
	}
}

// int main(void)
// {
// 	printf("%s\n", ft_itoa(0));
// 	printf("%s\n", ft_itoa(1));
// 	printf("%s\n", ft_itoa(125));
// 	printf("%s\n", ft_itoa(-125));
// 	printf("%s\n", ft_itoa(-1));
// 	printf("%s\n", ft_itoa(2147483647));
// 	printf("%s\n", ft_itoa(-2147483648));
// 	printf("%s\n", ft_itoa(2147483646));
// 	printf("%s\n", ft_itoa(-2147483647));
// }
