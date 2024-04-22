/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 13:00:11 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/26 13:00:11 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*free_check_directory(char *path, int *bool_malloc)
{
	if (*bool_malloc == 1)
		free(path);
	return (NULL);
}

static char	*malloc_check(char *str, char *path, int *bool_malloc)
{
	char	*new_str;

	new_str = ft_strdup(str);
	if (!new_str)
	{
		free_check_directory(path, bool_malloc);
		free_all(1, "malloc");
	}
	return (new_str);
}

char	*check_directory(char *path, int *b_free)
{
	struct stat	buf;

	if (stat(path, &buf) == -1)
	{
		if (errno != EACCES && errno != ENOENT && errno != ENOTDIR)
		{
			free_check_directory(path, b_free);
			free_all(1, "stat");
		}
		else if (errno == EACCES)
			return (malloc_check(": Permission denied\n", path, b_free));
		else
			return (malloc_check(": No such file or directory\n", path, b_free));
	}
	else if (!(buf.st_mode & S_IXUSR) || !(buf.st_mode & S_IFDIR))
	{
		if (!(buf.st_mode & S_IFDIR))
			return (malloc_check(": Not a directory\n", path, b_free));
		else
			return (malloc_check(": Permission denied\n", path, b_free));
	}
	return (NULL);
}
