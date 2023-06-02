/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minipipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 11:43:33 by jgirard-          #+#    #+#             */
/*   Updated: 2023/06/02 19:05:55 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	minilife(t_var	*var)
{
	close(var->fd);
	var->fd = open("/tmp/tmp.txt", O_RDONLY, 0777);
	dup2(var->fd, STDIN_FILENO);
}

void	minilife2(t_var	*var, t_lex	*lex)
{
	var->fd_s = open(lex->s[var->memo][0], O_RDWR, 0777);
	dup2(var->fd_s, STDIN_FILENO);
}

void	minilife3(t_var	*var)
{
	(n(), close(var->fd), var->fd = open("/tmp/tmp.txt", O_RDONLY, 0777));
	dup2(var->fd, STDIN_FILENO);
}

void	microredir(t_var *var)
{
	close(var->fd);
	var->fd = open("/tmp/tmp.txt", O_RDWR, 0777);
	dup2(var->fd, STDIN_FILENO);
}
