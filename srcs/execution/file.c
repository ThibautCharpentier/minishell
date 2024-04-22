/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/23 12:25:13 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/23 12:25:13 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	error_path(char *error, char *path, int exit)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(error, 2);
	g_var.last_exit = exit;
	if (g_var.pipe_idx < g_var.nb_pipe)
		close(g_var.pipe[g_var.pipe_idx][1]);
}

static char	*malloc_file(char *path)
{
	char	*pathname;

	pathname = ft_strdup(path);
	if (!pathname)
		free_all(1, "malloc");
	return (pathname);
}

void	run_file(t_com *lst_com, char *path)
{
	struct stat	buf;
	char		*pathname;

	if (stat(lst_com->command[0], &buf) == -1)
	{
		if (errno != EACCES && errno != ENOENT && errno != ENOTDIR)
			free_all(1, "stat");
		else if (errno == EACCES)
			error_path(": Permission denied\n", path, 126);
		else
			error_path(": No such file or directory\n", path, 127);
	}
	else if (!(buf.st_mode & S_IXUSR) || (buf.st_mode & S_IFDIR))
	{
		if (buf.st_mode & S_IFDIR)
			error_path(": Is a directory\n", path, 126);
		else
			error_path(": Permission denied\n", path, 126);
	}
	else
	{
		pathname = malloc_file(path);
		run_command(pathname, lst_com);
	}
}
