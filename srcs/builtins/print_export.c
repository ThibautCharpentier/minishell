/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:55:45 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/28 17:55:45 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	**start_malloc_env(int i_env)
{
	char	**env;

	env = malloc(sizeof(char *) * (i_env + 1));
	if (!env)
		free_all(1, "malloc");
	env[i_env] = NULL;
	return (env);
}

static char	**malloc_env(void)
{
	t_env	*tmp;
	int		i_env;
	char	**env;

	i_env = 0;
	tmp = g_var.lst_env;
	while (tmp)
	{
		if (!ft_same_str(tmp->key, "_"))
			i_env++;
		tmp = tmp->next;
	}
	env = start_malloc_env(i_env);
	tmp = g_var.lst_env;
	i_env = -1;
	while (tmp)
	{
		if (!ft_same_str(tmp->key, "_"))
		{
			env[++i_env] = NULL;
			env[i_env] = malloc_string_env(tmp, env);
		}
		tmp = tmp->next;
	}
	return (env);
}

static void	display_export(char **env, t_com *lst_com)
{
	int	i_env;
	int	j_env;

	i_env = -1;
	while (env[++i_env])
	{
		j_env = -1;
		ft_putstr_fd("declare -x ", what_fd(lst_com));
		while (env[i_env][++j_env])
		{
			ft_putchar_fd(env[i_env][j_env], what_fd(lst_com));
			if (env[i_env][j_env] == '=')
				ft_putchar_fd('"', what_fd(lst_com));
		}
		if (ft_strchr(env[i_env], '='))
			ft_putchar_fd('"', what_fd(lst_com));
		ft_putchar_fd('\n', what_fd(lst_com));
	}
	free_tabstr(env, 0);
}

void	print_export(t_com *lst_com)
{
	char	**env;
	int		i_env;
	int		j_env;
	char	*tmp;

	env = malloc_env();
	i_env = -1;
	while (env[++i_env])
	{
		j_env = i_env;
		while (env[++j_env])
		{
			if (ft_strcmp(env[i_env], env[j_env]) > 0)
			{
				tmp = env[i_env];
				env[i_env] = env[j_env];
				env[j_env] = tmp;
				i_env = 0;
				j_env = i_env;
			}
		}
	}
	display_export(env, lst_com);
}
