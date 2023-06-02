/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 11:17:09 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 12:54:20 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"
char	*ft_strdup_f(char *src)
{
	int		i;
	char	*p;

	i = 0;
	p = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (!p)
		return (0);
	while (src[i])
	{
		p[i] = src[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

char	*cpy_unset(char *s)
{
	int i;
	char *s1;

	i = 0;
	while (s[i] != '\0' && s[i] != '=')
		i++;
	s1 = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (s[i] != '\0' && s[i] != '=')
	{
		s1[i] = s[i];
		i++;
	}
	s1[i] = '\0';
	return (s1);
}

char	**export2(char **cenve, t_lex *lex, t_var *var, int i)
{
	char **retour;
	int j;
	char *char_unset;
	char **cenv;
	
	char_unset = cpy_unset(lex->s[var->z][i]);
	j = 0;
	cenv = unset(cenve, char_unset, var);
	retour = (char **)malloc(sizeof(char *) * (ft_strstrlen(cenv) + 2));
	while (cenv[j] != NULL)
	{
		retour[j] = ft_strdup_f(cenv[j]);
		j++;
	}
	retour[j] = ft_strdup(lex->s[var->z][i]);
	j++;
	retour[j] = NULL;
	free(char_unset);
	free_2(cenv);
	return (retour);
}
