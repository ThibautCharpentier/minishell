/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 19:40:30 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/08 19:40:30 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*fill_path(char *parse, char *path, int size)
{
	int	i;
	int	j;
	int	quote;

	i = 0;
	j = 0;
	quote = 0;
	while (is_space(parse[i]))
		i++;
	quote = 0;
	while (parse[i] && j < size)
	{
		if ((parse[i] == '\'' || parse[i] == '\"') && quote == 0)
		{
			quote++;
			i++;
			continue ;
		}
		path[j++] = parse[i++];
	}
	return (path);
}

static void	change_tab_limit(char *path, t_com *lst_com)
{
	lst_com->limit = malloc_limit(path, lst_com);
	if (lst_com->fd_read != 0)
		close(lst_com->fd_read);
	lst_com->fd_read = 0;
	lst_com->input = 1;
}

int	malloc_path(char *parse, int type, t_com *lst_com)
{
	int		size;
	char	*path;

	size = size_path(parse, 0);
	path = malloc(sizeof(char) * (size + 1));
	if (!path)
		free_all(1, "malloc");
	path[size] = '\0';
	g_var.parsing.path = fill_path(parse, path, size);
	if (type == 4)
		change_tab_limit(path, lst_com);
	else
	{
		if (!open_path(g_var.parsing.path, type, lst_com))
			return (0);
	}
	free(g_var.parsing.path);
	g_var.parsing.path = NULL;
	return (1);
}
