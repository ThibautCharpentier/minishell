/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 17:56:35 by igeorge           #+#    #+#             */
/*   Updated: 2022/06/09 17:56:35 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	path_error(char *str, char *path)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(str, 2);
	write(2, "\n", 1);
	free(path);
	g_var.parsing.path = NULL;
	return (0);
}

int	syntax_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	g_var.last_exit = 2;
	return (0);
}

int	print_command_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	g_var.last_exit = 1;
	return (0);
}

void	malloc_error(void)
{
	perror("malloc");
	exit(EXIT_FAILURE);
}
