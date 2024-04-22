/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 16:28:20 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/21 16:28:20 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	free_env(char **env, char *error)
{
	free_tabstr(env, 0);
	free_all(1, error);
}

char	*malloc_string_env(t_env *lst_env, char **env)
{
	char	*str;
	char	*str2;

	str = ft_strdup(lst_env->key);
	if (!str)
		free_env(env, "malloc");
	if (lst_env->value)
	{
		str2 = ft_strjoin(str, "=");
		free(str);
		if (!str2)
			free_env(env, "malloc");
		str = ft_strjoin(str2, lst_env->value);
		free(str2);
		if (!str)
			free_env(env, "malloc");
	}
	return (str);
}

int	what_fd(t_com *lst_com)
{
	if (lst_com->fd_write != 1)
		return (lst_com->fd_write);
	else if (g_var.pipe_idx == g_var.nb_pipe)
		return (1);
	else
		return (g_var.pipe[g_var.pipe_idx][1]);
}
