/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:51:21 by igeorge           #+#    #+#             */
/*   Updated: 2022/06/09 17:51:21 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell	g_var;

int	main(int argc, char **argv, char **env)
{
	(void) argv;
	if (argc != 1)
		return (syntax_error("too much parameters\n"));
	init(env);
	while (1)
	{
		get_line();
		if (!parse(g_var.line))
			continue ;
		execution();
		free_tabstr(g_var.path, 0);
		g_var.path = init_path(g_var.lst_env, 0);
	}
	free_all(0, "");
	return (0);
}
