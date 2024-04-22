/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_path.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:26:56 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/12 19:26:56 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**init_path(t_env *lst_env, int init)
{
	t_env	*tmp;
	char	**path;

	tmp = lst_env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->key, "PATH", 4))
		{
			if (tmp->value)
			{
				path = ft_split(tmp->value, ':');
				if (!path)
				{
					if (init == 1)
						free_lst_env(lst_env, 1);
					else
						free_all(1, "malloc");
				}
				return (path);
			}
		}
		tmp = tmp->next;
	}
	return (NULL);
}
