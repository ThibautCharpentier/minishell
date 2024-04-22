/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/04 19:35:44 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/04 19:35:44 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	reset_pid(void)
{
	g_var.pid = 0;
	if (g_var.pipe_idx < g_var.nb_pipe)
		close(g_var.pipe[g_var.pipe_idx][1]);
}

void	run_command(char *path, t_com *lst_com)
{
	int		status;

	g_var.pid = fork();
	if (g_var.pid == -1)
	{
		free(path);
		free_all(1, "fork");
	}
	else if (g_var.pid == 0)
		run_fork(path, lst_com);
	free(path);
	if (wait(&status) < 0)
	{
		kill(g_var.pid, SIGTERM);
		free_all(1, "wait");
	}
	if (WIFEXITED(status))
		g_var.last_exit = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		finish_process(WTERMSIG(status));
	reset_pid();
}

static void	not_found(t_com *tmp)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(tmp->command[0], 2);
	ft_putstr_fd(": Command not found\n", 2);
	g_var.last_exit = 127;
	if (g_var.pipe_idx < g_var.nb_pipe)
		close(g_var.pipe[g_var.pipe_idx][1]);
}

void	execution(void)
{
	t_com	*tmp;
	int		builtin;

	g_var.pipe_idx = -1;
	init_pipe();
	tmp = g_var.lst_com;
	while (++g_var.pipe_idx <= g_var.nb_pipe)
	{
		if (tmp->command)
		{
			builtin = check_builtins(tmp->command[0]);
			if (builtin <= B_EXIT)
				run_builtin(tmp, builtin);
			else if (!ft_strchr(tmp->command[0], '/'))
			{
				if (!run_path(tmp))
					not_found(tmp);
			}
			else
				run_file(tmp, tmp->command[0]);
		}
		tmp = tmp->next;
	}
	free_pipe(g_var.pipe);
	free_lst_com(g_var.lst_com);
}
