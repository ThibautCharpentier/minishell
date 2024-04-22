/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/09 17:29:34 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/09 17:29:34 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	new_link(t_com *tmp, t_com *lst_com, int i, int nbr_command)
{
	t_com	*new;

	if (i != nbr_command - 1)
	{
		new = malloc(sizeof(t_com));
		if (!new)
			free_lst_com(lst_com);
		tmp->next = new;
	}
}

static void	initialize_var(t_com *tmp)
{
	tmp->next = NULL;
	tmp->command = NULL;
	tmp->fd_read = 0;
	tmp->fd_write = 1;
	tmp->input = 0;
	tmp->str_input = NULL;
	tmp->limit = NULL;
}

t_com	*init_command(int nbr_command)
{
	int			i;
	t_com		*tmp;
	t_com		*lst_com;

	lst_com = NULL;
	if (nbr_command >= 1)
	{
		lst_com = malloc(sizeof(t_com));
		if (!lst_com)
			free_all(1, "malloc");
		i = -1;
		tmp = lst_com;
		while (++i < nbr_command)
		{
			initialize_var(tmp);
			new_link(tmp, lst_com, i, nbr_command);
			tmp = tmp->next;
		}
	}
	return (lst_com);
}
