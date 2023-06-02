/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollar_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:32:16 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 19:25:17 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	check_dol(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] != ' ')
			return (0);
		i++;
	}
	return (1);
}

int	check_redir(char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '<' && s[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_replace_dol_in(char *s, char *res)
{
	int		i;
	char	*s2;
	int		j;
	int		k;

	(n(), s2 = malloc(sizeof(char) * (ft_strlen(s)
				+ ft_strlen(res) - 1)), i = 0, j = 0, k = 0);
	while (s[i] != '\0')
	{
		k = 0;
		if (s[i] == '$' && s[i + 1] == '?')
		{
			i += 2;
			while (res[k] != '\0')
				(n(), s2[j] = res[k], j++, k++);
		}
		else
		{
			s2[j] = s[i];
			j++;
			i++;
		}
	}
	return (s2[j] = '\0', free(s), s2);
}

char	*dol_replace2(char *s, t_var *var, int p)
{
	int		i;
	char	*res;

	(n(), res = ft_itoa(var->last_err_com), i = 0);
	if (p == 1)
		while (s[i] != '\0' && s[i] != '=')
			i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
			{
				i++;
			}
			i++;
		}
		else if (s[i] == '$' && s[i + 1] == '?')
		{
			s = ft_replace_dol_in(s, res);
		}
		else
			i++;
	}
	return (free(res), s);
}

char	*replace_dol_env(char *s, int i)
{
	char	*s1;
	int		j;

	i++;
	j = i + 1;
	while (s[j] != '\0' && s[j] != ' '
		&& s[j] != '"' && s[j] != '\'' && s[j] != '$')
	{
		j++;
	}
	s1 = malloc(sizeof(char) * (j - i + 1));
	j = 0;
	while (s[i] != '\0' && s[i] != ' '
		&& s[i] != '"' && s[i] != '\'' && s[i] != '$')
	{
		s1[j] = s[i];
		j++;
		i++;
	}
	s1[j] = '\0';
	return (s1);
}
