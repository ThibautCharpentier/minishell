/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:49:15 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/09 17:49:15 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_option(char **command)
{
	int	i_com;
	int	j_com;

	i_com = 0;
	while (command[++i_com])
	{
		j_com = -1;
		if (command[i_com][++j_com] == '-' && command[i_com][j_com + 1])
		{
			while (command[i_com][++j_com])
			{
				if (command[i_com][j_com] != 'n')
					return (i_com);
			}
		}
		else
			return (i_com);
	}
	if (i_com == 1)
		return (-1);
	return (i_com);
}

void	run_echo(t_com *lst_com)
{
	int	i_com;
	int	option;
	int	fd;

	fd = what_fd(lst_com);
	option = 0;
	i_com = check_option(lst_com->command);
	if (i_com != 1 && i_com != -1)
		option = 1;
	if (i_com > 0)
	{
		while (lst_com->command[i_com])
		{
			ft_putstr_fd(lst_com->command[i_com], fd);
			if (lst_com->command[++i_com])
				ft_putchar_fd(' ', fd);
		}
	}
	if (!option)
		ft_putchar_fd('\n', fd);
	g_var.last_exit = 0;
}
