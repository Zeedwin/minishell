/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_dollard_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/26 10:32:16 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/26 12:51:35 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	check_redir(char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '<' && s[i + 1] == '<')
			return (1);
		i++;
	}
	return (0);
}

char *ft_replace_dol_in(char *s, char *res)
{
	int i;
	char *s2;
	int j;
	int k;

	s2 = malloc(sizeof(char) * (ft_strlen(s) + ft_strlen(res) - 1));
	i = 0;
	j = 0;
	k = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == '?')
		{
			i += 2;
			while (res[k] != '\0')
			{
				s2[j] = res[k];
				j++;
				k++;
			}
		}
		else
		{
			s2[j] = s[i];
			j++;
			i++;
		}
	}
	s2[j] = '\0';
	free(s);
	return (s2);
}

char	*dol_replace2(char *s, t_var *var)
{
	int i;
	char *res;

	res = ft_itoa(var->last_err_com);
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				i++;
			i++;
		}
		if (s[i] == '$' && s[i + 1] == '?')
		{
			s = ft_replace_dol_in(s, res);
		}
		i++;
	}
	return (s);
}

char	*replace_dol_env(char *s, int i)
{
	char	*s1;
	int	j;
	
	i++;
	j = i;
	while (s[j] != '\0' && s[j] != ' ' && s[j] != '"' && s[j] != '\'')
	{
		j++;
	}
	s1 = malloc(sizeof(char) * (j - i + 1));
	j = 0;
	while (s[i] != '\0' && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
	{
		s1[j] = s[i];
		j++;
		i++;
	}
	s1[j] = '\0';
	return (s1);
}

char	*replace_dol_env2(char *s, char **env)
{
	char *s1;
	int i;
	char *s2;
	int j;
	int k;

	i = 0;
	s1 = ft_strjoin(s, "=");
	j = ft_strlen(s1);
	k = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], s1, ft_strlen(s1)) == 0)
		{
			s2 = malloc(sizeof(char) * (ft_strlen(env[i]) - ft_strlen(s1) + 1));
			while (env[i][j] != '\0')
			{
				s2[k] = env[i][j];
				k++;
				j++;
			}
			s2[k] = '\0';
			return (s2);
		}
		i++;
	}
	s2 = malloc(sizeof(char));
	s2[0] = '\0';
	return(s2);
}

char *replace_dol_fi(char *s, char *s1, char *s2)
{
	char *s3;
	int i;
	int j;
	int k;

	i = 0;
	k = 0;
	j = 0;
	s3 = malloc(sizeof(char) * (ft_strlen(s) - ft_strlen(s1) + ft_strlen(s2) + 1));
	while (s[i] != '\0')
	{
		if (s[i] == '$' && s[i + 1] == s1[0])
		{
			while (s[i] != '\0' && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
				i++;
			while (s2[j] != '\0')
			{
				s3[k] = s2[j];
				k++;
				j++;
			}
		}
		else
		{
			s3[k] = s[i];
			k++;
			i++;
		}
	}
	s3[k] = '\0';
	return (s3);
}

char	*dol_replace3(char *s, char **env)
{
	char	*s1;
	char	*s2;
	int		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] != '\0' && s[i] != '\'')
				i++;
			i++;
		}
		if (s[i] == '$' && s[i + 1] != ' ')
		{
			s1 = replace_dol_env(s, i);
			s2 = replace_dol_env2(s1, env);
			s = replace_dol_fi(s, s1, s2);
		}
		i++;
	}
//	free(s1);
	free(s2);
	return (s);
}

char	***dol_replace1(char ***s, t_var *var, char **env)
{
	int	i;
	int	j;

	i = 0;
	while (s[i] != NULL)
	{
		j = 0;
		while (s[i][j] != NULL)
		{
			if (check_redir(s[i][j]) == 1)
				j++;
			else
			{
				s[i][j] = dol_replace2(s[i][j], var);
				s[i][j] = dol_replace3(s[i][j], env);
			}
			j++;
		}
		i++;
	}
	return (s);
}