/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childsupport.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 14:24:27 by jgirard-          #+#    #+#             */
/*   Updated: 2023/05/19 14:27:54 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "../includes/shell.h"

char	*idowanttopaychildsupport(t_init	ma, char *s)
{
	(norm(), ma.sf[ma.o] = s[ma.j], ma.j++, ma.o++);
	while (s[ma.j] != '\'')
		(norm(), ma.sf[ma.o] = s[ma.j], ma.j++, ma.o++);
	(norm(), ma.sf[ma.o] = s[ma.j], ma.j++, ma.o++);
	return (ma.sf);
}

char	*idontwanttopaychildsupport(t_init	ma, char *s)
{	
	while ((s[ma.j] == ' ' || s[ma.j] == '<') && s[ma.j] != '\0')
		(norm(), ma.sf[ma.o] = s[ma.j], ma.j++, ma.o++);
	while (s[ma.j] != ' ' && s[ma.j] != '|'
		&& s[ma.j] != '>' && s[ma.j] != '<' && s[ma.j] != '\0')
		(norm(), ma.sf[ma.o] = s[ma.j], ma.j++, ma.o++);
	return (ma.sf);
}
