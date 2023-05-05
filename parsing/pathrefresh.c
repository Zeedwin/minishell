/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathrefresh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 10:36:37 by hdelmann          #+#    #+#             */
/*   Updated: 2023/04/27 10:36:37 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include "../includes/shell.h"
#include <unistd.h>        // getcwd
#include <limits.h>

void	currpath(t_var *var)
{
	char	promt1[PATH_MAX];
	int		i;
	char	*promtf;

	if (getcwd(promt1, PATH_MAX) == NULL)
	{
		fprintf(stderr, "Cannot get current working directory path\n");
		if (errno == ERANGE)
		{
			fprintf(stderr, "Buffer size is too small.\n");
		}
		exit(EXIT_FAILURE);
	}
	var->promt = malloc((ft_strlen(promt1) + 2) * sizeof(char));
	promtf = var->promt;
	i = ft_strlen(promt1);
	promtf = ft_strcpy(promtf, promt1);
	promtf[i] = '>';
	promtf[i + 1] = '\0';
	promtf = ft_strjoin("\033[1;36m➜\033[1;32m", promtf);
	promtf = ft_strjoin(promtf, "\033[0m ");
	var->promt = ft_realloc(promtf, i);
	//free(promtf);
}
