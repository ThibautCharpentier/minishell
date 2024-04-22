/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:39:53 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/10 17:39:53 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init(char **env)
{
	init_signal();
	g_var.last_exit = 0;
	g_var.lst_com = NULL;
	g_var.line = NULL;
	g_var.pipe = NULL;
	g_var.lst_env = init_env(env);
	g_var.path = init_path(g_var.lst_env, 1);
	g_var.builtins = init_builtins();
	g_var.pid = 0;
	g_var.redirection = 0;
	g_var.parsing.parse = NULL;
	g_var.parsing.path = NULL;
}
