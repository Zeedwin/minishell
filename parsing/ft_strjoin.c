/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 20:34:24 by hdelmann          #+#    #+#             */
/*   Updated: 2022/11/25 14:19:09 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../includes/shell.h"

int	ft_strlen(const char *a)
{
	int	i;

	i = 0;
	while (a && a[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen2(const char *a)
{
	int	i;

	i = 0;
	while (a && a[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s3;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc(sizeof(*s3) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
	{
		s3[i] = s2[j];
		i++;
		j++;
	}
	s3[i] = 0;
	return (s3);
}

char	*ft_strjoin_free(char *s1, char *s2, int freeable)
{
	char			*s3;
	unsigned int	i;
	unsigned int	j;

	if (!s1 || !s2)
		return (0);
	s3 = (char *)malloc(sizeof(*s3) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!s3)
		return (0);
	i = 0;
	j = 0;
	while (s1[i] != 0)
	{
		s3[i] = s1[i];
		i++;
	}
	while (s2[j] != 0)
		s3[i++] = s2[j++];
	s3[i] = 0;
	if ((freeable & 1) != 0)
		free(s1);
	if ((freeable & 2) != 0)
		free(s2);
	return (s3);
}
