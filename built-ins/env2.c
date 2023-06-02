/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 14:39:21 by jgirard-          #+#    #+#             */
/*   Updated: 2023/06/02 15:37:37 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../includes/shell.h"

void	env(char **cpyenv)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	j = 0;
	i = 0;
	while (cpyenv[i])
	{
		j = 0;
		while (cpyenv[i][j])
		{
			if (cpyenv[i][j] == '=')
				flag = 1;
			j++;
		}
		if (flag == 1)
			printf("%s\n", cpyenv[i]);
		flag = 0;
		i++;
	}
}
