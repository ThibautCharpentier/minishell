/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:36:40 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/11 13:36:40 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	finish_process(int sig)
{
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("minishell: quit:\n", 1);
		g_var.last_exit = 131;
	}
	else if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		g_var.last_exit = 130;
	}
}

static void	finish_redirection(void)
{
	if (g_var.pid)
	{
		if (kill(g_var.pid, SIGTERM))
			free_all(1, "kill");
		g_var.last_exit = 130;
		ft_putchar_fd('\n', 1);
	}
}

void	signal_received(int sig)
{
	if (g_var.redirection == 1)
		finish_redirection();
	else if (g_var.pid == 0)
	{
		if (sig == SIGINT)
		{
			g_var.last_exit = 130;
			ft_putchar_fd('\n', 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else if (sig == SIGQUIT)
		{
			rl_on_new_line();
			rl_redisplay();
		}
	}
}

void	remove_signal(void)
{
	signal(SIGINT, NULL);
	signal(SIGQUIT, NULL);
}

void	init_signal(void)
{
	signal(SIGINT, &signal_received);
	signal(SIGQUIT, &signal_received);
}
