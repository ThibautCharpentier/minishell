/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/30 18:07:08 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/30 18:07:08 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**get_lst_env(t_env *lst_env)
{
	t_env	*tmp;
	int		i_env;
	char	**env;

	i_env = 0;
	tmp = lst_env;
	while (tmp)
	{
		i_env++;
		tmp = tmp->next;
	}
	env = malloc(sizeof(char *) * (i_env + 1));
	if (!env)
		free_all(1, "malloc");
	env[i_env] = NULL;
	tmp = g_var.lst_env;
	i_env = -1;
	while (tmp)
	{
		env[++i_env] = NULL;
		env[i_env] = malloc_string_env(tmp, env);
		tmp = tmp->next;
	}
	return (env);
}

static void	copy_stdout(t_com *lst_com, char **env, char *path)
{
	int	fd;

	fd = 0;
	if (lst_com->fd_write != 1)
		fd = dup2(lst_com->fd_write, 1);
	else if (g_var.pipe_idx != g_var.nb_pipe)
	{
		close(g_var.pipe[g_var.pipe_idx][0]);
		fd = dup2(g_var.pipe[g_var.pipe_idx][1], 1);
	}
	if (fd < 0)
	{
		free(path);
		free_tabstr(env, 0);
		free_all(1, "dup2");
	}
}

static int	pipe_str_input(t_com *lst_com, char **env, char *path)
{
	int	pipe_fd[2];
	int	fd;

	if (pipe(pipe_fd) == -1)
	{
		free(path);
		free_tabstr(env, 0);
		free_all(1, "pipe");
	}
	ft_putstr_fd(lst_com->str_input, pipe_fd[1]);
	close(pipe_fd[1]);
	fd = dup2(pipe_fd[0], 0);
	return (fd);
}

static void	copy_stdin(t_com *lst_com, char **env, char *path)
{
	int	fd;

	fd = 0;
	if (lst_com->fd_read != 0)
		fd = dup2(lst_com->fd_read, 0);
	else if (lst_com->input == 1)
		fd = pipe_str_input(lst_com, env, path);
	else if (g_var.pipe_idx != 0)
		fd = dup2(g_var.pipe[g_var.pipe_idx - 1][0], 0);
	if (fd < 0)
	{
		free(path);
		free_tabstr(env, 0);
		free_all(1, "dup2");
	}
}

void	run_fork(char *path, t_com *lst_com)
{
	char	**env;

	remove_signal();
	env = get_lst_env(g_var.lst_env);
	copy_stdin(lst_com, env, path);
	copy_stdout(lst_com, env, path);
	execve(path, lst_com->command, env);
	free(path);
	free_tabstr(env, 0);
	free_all(1, "execve");
}
