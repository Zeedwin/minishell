/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/27 21:23:57 by jgirard-          #+#    #+#             */
/*   Updated: 2022/03/30 00:02:22 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_wcount(char const *s, char c)
{
	int	i;
	int	wc;

	wc = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			wc++;
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	return (wc);
}

static char	*ft_cut(char const *s, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] != c && s[i])
	{
		i++;
	}
	word = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != c && s[i])
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**splited;
	int		i;
	int		j;

	j = 0;
	i = 0;
	splited = malloc(sizeof(char *) * (ft_wcount(s, c) + 1));
	while (s[i])
	{
		if (s[i] != c)
		{
			splited[j++] = ft_cut(s + i, c);
			while (s[i] != c && s[i])
				i++;
		}
		else
			i++;
	}
	splited[j] = NULL;
	return (splited);
}

/*int main()
{
	char **split = ft_split("hello world erge re rgerg erg", ' ');
	int	j;

	j = 0;
	while (split[j])
	{
		printf("-> %s\n", split[j]);
		j++;
	}
}*/