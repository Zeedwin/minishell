/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_7.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 13:57:24 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 20:44:23 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	mini_redir_s1(t_lex *lex, t_var *var)
{
	int	i;

	i = 0;
	while (lex->s[var->z][0] == NULL &&
			(lex->supatok[var->z + i] == TK_REDIR_S
			|| lex->supatok[var->z + i] == TK_REDIR_E
			|| lex->supatok[var->z + i] == TK_REDIR_S2
			|| lex->supatok[var->z + i] == TK_REDIR_E2))
	{
		if (lex->s[var->z + i + 2][1] != NULL)
		{
			lex->s[var->z][0] = ft_strdup(lex->s[var->z + i + 2][1]);
			var->c = var->z + i + 2;
		}
		i += 2;
	}
}

char	**add_if_after(char **s1)
{
	int		i;
	int		j;
	char	**s2;

	i = 0;
	j = 1;
	s2 = malloc(sizeof(char *) * (ft_strstrlen(s1) + 1));
	while (s1[j] != NULL)
	{
		s2[i] = malloc(sizeof(char) * (ft_strlen(s1[j]) + 1));
		s2[i] = ft_strcpy(s2[i], s1[j]);
		i++;
		j++;
	}
	s2[i] = NULL;
	return (s2);
}

int	redir_n2(t_var *var, t_lex *lex)
{
	if (var->fd_s != -2)
		close (var->fd_s);
	var->fd_s = open(lex->s[var->z + var->i + 1][0],
			O_CREAT | O_APPEND | O_WRONLY, 0777);
	if (var->fd_s == -1 && errno == EACCES)
	{
		if (var->fail_dir == 0)
			printf("bash: permission denied: %s\n",
				lex->s[var->z + var->i + 1][0]);
		var->fail_dir = 1;
		g_global.last_err_com = 1;
		return (1);
	}
	var->memo = var->z + var->i + 1;
	return (0);
}

int	miniredir_s4(t_lex *lex, t_var *var)
{
	if (lex->supatok[var->z + var->i] == TK_REDIR_S2)
	{
		redir_n2(var, lex);
	}
	else if (lex->supatok[var->z + var->i] == TK_REDIR_E2)
	{
		var->did_fail |= break_p(lex, var);
		if (var->fd_e != -2)
			close (var->fd_e);
		var->fd_e = open("/tmp/tmp.txt", O_RDWR, 0777);
	}
	if (var->z > 0 && var->check_after_redir == 0)
		lex->s[var->z - 1] = add_after_redir(
				lex->s[var->z - 1],
				lex->s[var->z + var->i + 1], var->c);
	if (var->z > 0 && var->check_after_redir == 1 && var->i > 0)
		lex->s[var->z - 1] = add_after_redir(
				lex->s[var->z - 1],
				lex->s[var->z + var->i + 1], var->o);
	(n(), var->i += 2, var->o = 0);
	return (0);
}

char	*dol_replace3(char *s, char **env, int p)
{
	char	*s1;
	char	*s2;
	int		i;

	i = 0;
	if (p == 1)
		while (s[i] != '\0' && s[i] != '=')
			i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
				i = ini_i(s, i);
		else if (s[i] == '$' && s[i + 1] != ' ' && s[i + 1] != '\0'
			&& s[i + 1] != '"' && s[i + 1] != '\'' && s[i + 1] != '$')
		{
			(n(), s1 = replace_dol_env(s, i), s2 = replace_dol_env2(s1, env));
			(n(), s = dolr_n(s1, s2, s), free(s1), free(s2));
		}
		else
			i++;
	}
	return (s);
}
