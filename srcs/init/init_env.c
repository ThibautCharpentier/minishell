/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 19:26:21 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/12 19:26:21 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	new_link(char *env, t_env *tmp, t_env *lst_env)
{
	t_env	*new;

	if (env)
	{
		new = malloc(sizeof(t_env));
		if (!new)
			free_lst_env(lst_env, 1);
		tmp->next = new;
	}
}

t_env	*init_env(char **env)
{
	int		i_env;
	t_env	*tmp;
	t_env	*lst_env;

	lst_env = NULL;
	if (env && env[0])
	{
		lst_env = malloc(sizeof(t_env));
		if (!lst_env)
			malloc_error();
		i_env = 0;
		tmp = lst_env;
		while (env[i_env])
		{
			tmp->next = NULL;
			tmp->key = ft_strprechr(env[i_env], '=');
			tmp->value = ft_strpostchr(env[i_env], '=');
			if (!tmp->key || !tmp->value)
				free_lst_env(lst_env, 1);
			i_env++;
			new_link(env[i_env], tmp, lst_env);
			tmp = tmp->next;
		}
	}
	return (lst_env);
}
