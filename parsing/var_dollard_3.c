/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollard_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 15:35:19 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/27 16:18:23 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

char	*replace_no_dol(char *s, char *s1)
{
	char	*s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s2 = malloc(sizeof(char) * (ft_strlen(s) - ft_strlen(s1) + 1));
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == s1[0])
		{
			i++;
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '$')
				i++;
		}
		else
		{
			s2[j] = s[i];
			i++;
			j++;
		}
	}
	s2[j] = '\0';
	if (ft_strlen(s2) == 0)
	{
		free(s2);
		free(s);
		s = ft_strdup("");
		return (s);
	}
	free(s);
	return (s2);
}
