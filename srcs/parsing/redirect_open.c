/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_open.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:31:41 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/08 19:31:41 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	close_fd(int type, t_com *lst_com)
{
	if (type == 1 || type == 2)
	{
		if (lst_com->fd_write > 1)
			close(lst_com->fd_write);
	}
	else if (type == 3)
	{
		if (lst_com->fd_read > 0)
			close(lst_com->fd_read);
	}
}

int	open_path(char *path, int type, t_com *lst_com)
{
	close_fd(type, lst_com);
	if (type == 1)
		lst_com->fd_write = open(path, O_WRONLY | O_TRUNC | O_CREAT, 0777);
	else if (type == 2)
		lst_com->fd_write = open(path, O_WRONLY | O_APPEND | O_CREAT, 0777);
	else if (type == 3)
	{
		lst_com->fd_read = open(path, O_RDONLY);
		lst_com->input = 0;
	}
	if (lst_com->fd_write == -1 || lst_com->fd_read == -1)
	{
		g_var.last_exit = 1;
		if (errno != EACCES && errno != ENOENT && errno != ENOTDIR)
			free_all(1, "open");
		else if (errno == ENOTDIR || errno == ENOENT)
			return (path_error(": No such file or directory ", path));
		else
			return (path_error(": Permission denied ", path));
	}
	return (1);
}
