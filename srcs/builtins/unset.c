/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 14:21:46 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/30 14:21:46 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	unset_env(char *arg)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = g_var.lst_env;
	while (tmp)
	{
		if (ft_same_str(tmp->key, arg))
		{
			if (tmp == g_var.lst_env)
				g_var.lst_env = tmp->next;
			else
				tmp2->next = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		tmp2 = tmp;
		tmp = tmp-> next;
	}
}

static int	check_arg_unset(char *arg)
{
	int	i_arg;
	int	alpha;

	if (!arg[0])
		return (0);
	i_arg = -1;
	alpha = 0;
	while (arg[++i_arg])
	{
		if (ft_isalpha(arg[i_arg]) || arg[i_arg] == '_')
			alpha = 1;
		else if (ft_isdigit(arg[i_arg]) && !alpha)
			return (0);
		else if (!ft_isdigit(arg[i_arg]) && arg[i_arg] != '_')
			return (0);
	}
	return (1);
}

void	run_unset(t_com *lst_com)
{
	int	i_com;

	g_var.last_exit = 0;
	if (!lst_com->command[1])
		return ;
	i_com = 0;
	while (lst_com->command[++i_com])
	{
		if (!check_arg_unset(lst_com->command[i_com]))
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(lst_com->command[i_com], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.last_exit = 1;
		}
		else if (g_var.nb_pipe == 0
			&& !ft_same_str(lst_com->command[i_com], "_"))
			unset_env(lst_com->command[i_com]);
	}
}
