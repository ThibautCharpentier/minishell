/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:52:54 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/01 14:52:54 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	nb_too_high(char *arg, char *cmp)
{
	int	i_arg;

	i_arg = 0;
	while (arg[i_arg] >= '0' && arg[i_arg] <= '9')
	{
		if (arg[i_arg] < cmp[i_arg])
			return (0);
		else if (arg[i_arg] > cmp[i_arg])
			return (1);
		i_arg++;
	}
	return (0);
}

static void	error_exit(char *arg)
{
	g_var.last_exit = 255;
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	if (g_var.nb_pipe != 0)
		return ;
	ft_putstr_fd("logout\n", 1);
	free_all(0, "");
}

static void	add_res(int i_arg, char *arg, long long *res, int sign)
{
	int	nb_digit;

	nb_digit = 0;
	while (arg[i_arg] >= '0' && arg[i_arg] <= '9')
	{
		*res = *res * 10 + arg[i_arg] - '0';
		nb_digit++;
		if (nb_digit == 20)
		{
			error_exit(arg);
			return ;
		}
		i_arg++;
	}
	if (arg[i_arg])
		error_exit(arg);
	else if (nb_digit == 19)
	{
		if (sign == 1 && nb_too_high(arg + i_arg - 19, "9223372036854775807"))
			error_exit(arg);
		else if (sign == -1
			&& nb_too_high(arg + i_arg - 19, "9223372036854775808"))
			error_exit(arg);
	}
}

static long	atoi_exit(char *arg)
{
	int			i_arg;
	long long	sign;
	long long	res;

	res = 0;
	sign = 1;
	i_arg = 0;
	while (arg[i_arg] == ' ' || arg[i_arg] == '\f' || arg[i_arg] == '\n'
		|| arg[i_arg] == '\r' || arg[i_arg] == '\t' || arg[i_arg] == '\v')
		i_arg++;
	if (arg[i_arg] == '+' || arg[i_arg] == '-')
	{
		if (arg[i_arg] == '-')
			sign = -1;
		i_arg++;
	}
	while (arg[i_arg] == '0')
		i_arg++;
	add_res(i_arg, arg, &res, sign);
	return (res * sign);
}

void	run_exit(t_com *lst_com)
{
	long	nb_exit;

	g_var.last_exit = 0;
	if (!lst_com->command[1] && g_var.nb_pipe == 0)
	{
		ft_putstr_fd("logout\n", 1);
		free_all(0, "");
	}
	if (lst_com->command[1])
	{
		nb_exit = atoi_exit(lst_com->command[1]);
		if (g_var.last_exit == 2)
			return ;
		if (lst_com->command[2] && g_var.last_exit != 255)
		{
			print_command_error("exit: too many arguments\n");
			return ;
		}
		g_var.last_exit = nb_exit % 256;
		if (g_var.nb_pipe != 0)
			return ;
		ft_putstr_fd("logout\n", 1);
		free_all(0, "");
	}
}
