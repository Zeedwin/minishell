/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 20:37:55 by jgirard-          #+#    #+#             */
/*   Updated: 2023/04/27 20:38:02 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	pwd(void)
{
	char	promt1[PATH_MAX];
	char	*pwd;

	pwd = getcwd(promt1, PATH_MAX);
	printf("%s\n", pwd);
}
