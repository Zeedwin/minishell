/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdelmann <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:46:06 by hdelmann          #+#    #+#             */
/*   Updated: 2023/06/02 14:09:41 by hdelmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	process_init(t_lex *lex, t_var *var)
{
	init_tab(lex, var->line, g_global.cpyenv, var);
	tokenizer(lex);
	lex->s = separate_tok(var, lex, lex->s);
	lex->s = dol_replace1(lex->s, var, g_global.cpyenv);
	lex->s = del_brak(lex->s);
	turbotokenizer(lex);
	creat_pid(lex, var);
}
