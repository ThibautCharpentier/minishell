/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 11:51:34 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/01 11:51:34 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_env(t_com *lst_com)
{
	t_env	*tmp;

	if (lst_com->command[1])
	{
		print_command_error("env: too many arguments\n");
		return ;
	}
	g_var.last_exit = 0;
	tmp = g_var.lst_env;
	while (tmp)
	{
		if (tmp->value)
		{
			ft_putstr_fd(tmp->key, what_fd(lst_com));
			ft_putchar_fd('=', what_fd(lst_com));
			ft_putstr_fd(tmp->value, what_fd(lst_com));
			ft_putchar_fd('\n', what_fd(lst_com));
		}
		tmp = tmp->next;
	}
}
