/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 20:06:10 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/04 20:06:10 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_pipe(void)
{
	int	i_pipe;

	if (g_var.nb_pipe != 0)
	{
		g_var.pipe = malloc(sizeof(int *) * g_var.nb_pipe);
		if (!g_var.pipe)
			free_all(1, "malloc");
		ft_bzero(g_var.pipe, sizeof(int *) * g_var.nb_pipe);
		i_pipe = -1;
		while (++i_pipe < g_var.nb_pipe)
		{
			g_var.pipe[i_pipe] = malloc(sizeof(int) * 2);
			if (!g_var.pipe[i_pipe])
			{
				g_var.nb_pipe = i_pipe;
				free_all(1, "malloc");
			}
			ft_bzero(g_var.pipe[i_pipe], sizeof(int) * 2);
			if (pipe(g_var.pipe[i_pipe]) == -1)
			{
				g_var.nb_pipe = i_pipe + 1;
				free_all(1, "pipe");
			}
		}
	}
}
