/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 16:31:54 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/28 16:31:54 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	set_export(char *arg)
{
	char	*key;
	char	*value;
	int		error;

	if (ft_strchr(arg, '='))
	{
		key = ft_strprechr(arg, '=');
		value = ft_strpostchr(arg, '=');
		if (!value || !key)
		{
			free(key);
			free(value);
			free_all(1, "malloc");
		}
		error = set_env(key, value);
		free(key);
		free(value);
		if (!error)
			free_all(1, "malloc");
	}
	else if (!set_env(arg, NULL))
		free_all(1, "malloc");
}

static int	check_arg_export(char *arg)
{
	int	i_arg;
	int	alpha;

	if (arg[0] == '=' || !arg[0])
		return (0);
	i_arg = -1;
	alpha = 0;
	while (arg[++i_arg] && arg[i_arg] != '=')
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

static int	check_name_export(char *arg)
{
	char	*str;

	str = ft_strprechr(arg, '=');
	if (!str)
		free_all(1, "malloc");
	if (ft_same_str(str, "_"))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}

void	run_export(t_com *lst_com)
{
	int	i_com;

	g_var.last_exit = 0;
	if (!lst_com->command[1])
	{
		print_export(lst_com);
		return ;
	}
	i_com = 0;
	while (lst_com->command[++i_com])
	{
		if (!check_arg_export(lst_com->command[i_com]))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(lst_com->command[i_com], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			g_var.last_exit = 1;
		}
		else if (g_var.nb_pipe == 0
			&& check_name_export(lst_com->command[i_com]))
			set_export(lst_com->command[i_com]);
	}
}
