/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgirard- <jgirard-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/27 12:46:06 by hdelmann          #+#    #+#             */
/*   Updated: 2023/05/29 23:25:13 by jgirard-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/shell.h"

void	process_init(t_lex *lex, t_var *var)
{
	init_tab(lex, var->line, var->cpyenv, var);
	tokenizer(lex);
	lex->s = separate_tok(var, lex, lex->s);
	lex->s = dol_replace1(lex->s, var, g_global.cpyenv);
	lex->s = del_brak(lex->s);
	turbotokenizer(lex);
	creat_pid(lex, var);
}
