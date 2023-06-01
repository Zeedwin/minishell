/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cpytrichar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:28:05 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/01 12:20:07 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	lentrichar(char ***s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

int	lendoubchar(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
	{
		i++;
	}
	return (i);
}

char	***cpytrichar(char ***s, int decale)
{
	char	***sf;
	int		i;
	int		j;
	int		k;

	(n(), k = 0, i = 0, sf = malloc(sizeof(char **) * (lentrichar(s) + 2)));
	while (s[k] != NULL)
	{
		if (k == decale)
			(n(), sf[i] = malloc(sizeof(char *) * 2),
				sf[i][0] = NULL, sf[i][1] = NULL, i++);
		j = 0;
		sf[i] = malloc(sizeof(char *) * (lendoubchar(s[k]) + 1));
		while (s[k][j] != NULL)
		{
			sf[i][j] = ft_strdup(s[k][j]);
			j++;
		}
		sf[i][j] = NULL;
		i++;
		k++;
	}
	sf[i] = NULL;
	free_3(s);
	return (sf);
}
