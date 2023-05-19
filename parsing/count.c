/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 15:03:32 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/19 13:52:29 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

int	count3(int i, char *s, int code)
{
	if (code == 3)
	{
		i++;
		while (s[i] != '\'' && s[i] != '\0')
		{
			i++;
			if (s[i - 1] == '\\' && s[i] == '\'')
				i++;
		}
	}
	return (i + 1);
}

int	count2(int i, char *s, int code)
{
	if (code == 0)
	{
		i++;
		while (s[i] != '"' && s[i] != '\0')
		{
			i++;
			if (s[i - 1] == '\\' && s[i] == '"')
				i++;
		}
		return (i + 1);
	}
	if (code == 1)
		while (s[i] != '\0' && s[i] == ' ')
			i++;
	if (code == 2)
		while (s[i] != ' ' && s[i] != '"' && s[i] != '\0' && s[i] != '\''
			&& s[i] != '|' && s[i] != '>' && s[i] != '<' )
			i++;
	return (i);
}

void	count5(char *s, t_var *var, int code)
{
	if (code == 4)
	{
		var->counti++;
		var->countj++;
	}
	else if (code == 3)
	{
		var->countj++;
		var->counti = count3(var->counti, s, code);
	}
	else
	{
		var->countj++;
		var->counti = count2(var->counti, s, code);
	}
}

int	count(char *s, t_var *var)
{
	var->counti = 0;
	var->countj = 0;
	while (s[var->counti] != '\0')
	{
		if (s[var->counti] == '"')
			count5(s, var, 0);
		else if (s[var->counti] == '\'')
			count5(s, var, 3);
		else if (s[var->counti] == ' ')
			var->counti = count2(var->counti, s, 1);
		else if ((s[var->counti] == '|') || (s[var->counti] == '<'
				&& s[var->counti + 1] != '<') || (s[var->counti] == '>'
				&& s[var->counti + 1] != '>'))
			count5(s, var, 4);
		else if ((s[var->counti] == '<' && s[var->counti + 1] == '<')
			|| (s[var->counti] == '>' && s[var->counti + 1] == '>'))
		{
			var->counti = var->counti + 2;
			var->countj++;
		}
		else
			count5(s, var, 2);
	}
	return (var->countj);
}
