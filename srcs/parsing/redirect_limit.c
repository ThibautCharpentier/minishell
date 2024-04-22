/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_limit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 18:07:03 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/13 18:07:03 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	size_limit(char **limit)
{
	int	i;

	i = 0;
	while (limit && limit[i])
		i++;
	return (i);
}

static void	fill_limit(char **new, char **old, char *path)
{
	int	i;

	i = 0;
	while (old && old[i])
	{
		new[i] = ft_strdup(old[i]);
		if (!new[i])
		{
			free_tabstr(new, 0);
			free_all(1, "malloc");
		}
		i++;
	}
	new[i] = ft_strdup(path);
	if (!new[i])
	{
		free_tabstr(new, 0);
		free_all(1, "malloc");
	}
}

char	**malloc_limit(char *path, t_com *lst_com)
{
	char	**limit;
	int		size;

	size = size_limit(lst_com->limit) + 1;
	limit = malloc(sizeof(char *) * (size + 1));
	if (!limit)
		free_all(1, "malloc");
	limit[size] = NULL;
	fill_limit(limit, lst_com->limit, path);
	free_tabstr(lst_com->limit, 0);
	return (limit);
}
