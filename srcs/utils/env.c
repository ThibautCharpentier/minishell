/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 18:52:59 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/25 18:52:59 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_env(char *the_key)
{
	t_env	*tmp;

	tmp = g_var.lst_env;
	while (tmp)
	{
		if (ft_same_str(tmp->key, the_key))
			return (tmp->value);
		tmp = tmp->next;
	}
	return (NULL);
}

static int	add_env(char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	tmp = g_var.lst_env;
	while (tmp->next)
		tmp = tmp->next;
	new = malloc(sizeof(t_env));
	if (!new)
		return (0);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!new->key || (!new->value && value))
	{
		free(new->key);
		free(new->value);
		free(new);
		return (0);
	}
	tmp->next = new;
	return (1);
}

static t_env	*env_init(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	if (value)
		new->value = ft_strdup(value);
	else
		new->value = NULL;
	new->next = NULL;
	if (!new->key || (!new->value && value))
	{
		free(new->key);
		free(new->value);
		free(new);
		return (NULL);
	}
	return (new);
}

static int	put_env(t_env *tmp, char *value)
{
	if (!value)
		return (1);
	free(tmp->value);
	tmp->value = ft_strdup(value);
	if (!tmp->value)
		return (0);
	return (1);
}

int	set_env(char *key, char *value)
{
	t_env	*tmp;

	if (!g_var.lst_env)
		g_var.lst_env = env_init(key, value);
	else
	{
		tmp = g_var.lst_env;
		while (tmp)
		{
			if (ft_same_str(tmp->key, key))
			{
				if (!put_env(tmp, value))
					return (0);
				return (1);
			}
			tmp = tmp->next;
		}
		return (add_env(key, value));
	}
	if (!g_var.lst_env)
		return (0);
	return (1);
}
