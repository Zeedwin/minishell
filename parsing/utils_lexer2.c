/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_lexer2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:49:37 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/27 13:46:36 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*space(char *s)
{
	char	*s1;

	if (!s)
		return (NULL);
	if (s[0] == '$')
	{
		s1 = ft_strjoin(" ", s);
		free(s);
		return (s1);
	}
	return (s);
}

int	point(char *s)
{
	if (!s)
		return (2);
	if (ft_strlen(s) == 2 && s[0] == '.' && s[1] == '.')
		return (1);
	if (ft_strlen(s) == 1 && (s[0] == '.' || s[0] == '$'))
		return (1);
	if (ft_strlen(s) == 1 && s[0] == 'a')
		return (1);
	if (ft_strlen(s) >= 2 && s[0] == 'r' && s[1] == 'r')
		return (1);
	if (ft_strlen(s) >= 2 && s[0] == '.' && s[1] == '/'
		&& (s[3] == ' ' || s[3] == '\0'))
		return (0);
	if (ft_strlen(s) >= 1 && ((s[0] == 'q' && s[1] == '\0')
			|| (s[0] == '"' && s[1] == '\0')))
		return (1);
	return (2);
}

int	check_vide(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] >= 33 && s[i] <= 126)
			return (1);
		i++;
	}
	return (0);
}

char	*suppr_pos(char *s, int pos)
{
	char	*s1;
	int		i;
	int		j;

	s1 = malloc(sizeof(char) * ft_strlen(s));
	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		if (i != pos)
		{
			s1[j] = s[i];
			j++;
		}
		i++;
	}
	s1[j] = '\0';
	free(s);
	return (s1);
}
