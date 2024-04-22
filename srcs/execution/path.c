/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 12:47:58 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/06 12:47:58 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*malloc_pathname(char *path, char *command)
{
	char	*pathname;
	char	*tmp;

	if (path[ft_strlen(path) - 1] == '/')
	{
		pathname = ft_strjoin(path, command);
		if (!pathname)
			free_all(1, "malloc");
	}
	else
	{
		tmp = ft_strjoin(path, "/");
		if (!tmp)
			free_all(1, "malloc");
		pathname = ft_strjoin(tmp, command);
		free(tmp);
		if (!pathname)
			free_all(1, "malloc");
	}
	return (pathname);
}

static char	*check_bin(char *path, char *command, int *error)
{
	char		*pathname;
	struct stat	buf;

	pathname = malloc_pathname(path, command);
	if (stat(pathname, &buf) == -1)
	{
		free(pathname);
		free_all(1, "stat");
	}
	else if (!(buf.st_mode & S_IXUSR))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(command, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		g_var.last_exit = 126;
		free(pathname);
		*error = 1;
		if (g_var.pipe_idx < g_var.nb_pipe)
			close(g_var.pipe[g_var.pipe_idx][1]);
		return (NULL);
	}
	return (pathname);
}

static char	*check_dir(char *path, char *command)
{
	DIR				*dir;
	struct dirent	*buf;

	dir = opendir(path);
	if (!dir)
	{
		if (errno != EACCES && errno != ENOENT && errno != ENOTDIR)
			free_all(1, "opendir");
		return (NULL);
	}
	buf = readdir(dir);
	while (buf)
	{
		if (buf->d_type == DT_REG && ft_same_str(buf->d_name, command))
		{
			closedir(dir);
			return (path);
		}
		buf = readdir(dir);
	}
	closedir(dir);
	return (NULL);
}

static char	*check_path(char *command, int *error)
{
	int		i_path;
	char	*path;

	i_path = -1;
	while (g_var.path[++i_path])
	{
		path = check_dir(g_var.path[i_path], command);
		if (path)
			return (check_bin(path, command, error));
	}
	return (NULL);
}

int	run_path(t_com *lst_com)
{
	char	*path;
	int		error;

	if (!g_var.path || !g_var.path[0] || !g_var.path[0][0])
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(lst_com->command[0], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_var.last_exit = 127;
		if (g_var.pipe_idx < g_var.nb_pipe)
			close(g_var.pipe[g_var.pipe_idx][1]);
		return (1);
	}
	error = 0;
	path = check_path(lst_com->command[0], &error);
	if (error)
		return (1);
	if (!path)
		return (0);
	run_command(path, lst_com);
	return (1);
}
