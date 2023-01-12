/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 15:48:43 by hdelmann          #+#    #+#             */
/*   Updated: 2022/11/09 15:55:08 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	ft_mots(char const *str, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			i++;
		else
		{
			j++;
			while (str[i] && str[i] != c)
			i++;
		}
	}
	return (j);
}

static char	*ft_mettre(char *mot, char const *s, int i, int len)
{
	int	j;

	j = 0;
	while (len > 0)
	{
		mot[j] = s[i - len];
		j++;
		len--;
	}
	mot[j] = '\0';
	return (mot);
}

static char	**ft_sep(char const *s, char c, char **s2, int num)
{
	int	i;
	int	mot;
	int	len;

	i = 0;
	mot = 0;
	len = 0;
	while (mot < num)
	{
		while (s[i] && s[i] == c)
			i++;
		while (s[i] && s[i] != c)
		{
			i++;
			len++;
		}
		s2[mot] = (char *)malloc(sizeof(char) * (len + 1));
		if (!s2)
			return (0);
		ft_mettre(s2[mot], s, i, len);
		len = 0;
		mot++;
	}
	s2[mot] = 0;
	return (s2);
}

char	**ft_split(char const *s, char c)
{
	char			**s2;
	unsigned int	num;

	if (!s)
		return (0);
	num = ft_mots(s, c);
	s2 = (char **)malloc(sizeof(char *) * (num + 1));
	if (!s2)
		return (0);
	ft_sep(s, c, s2, num);
	return (s2);
}
