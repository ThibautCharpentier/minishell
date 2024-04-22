/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 12:05:31 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/30 12:05:31 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_pwd(t_com *lst_com)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
		free_all(1, "getcwd");
	ft_putstr_fd(pwd, what_fd(lst_com));
	ft_putchar_fd('\n', what_fd(lst_com));
	free(pwd);
	g_var.last_exit = 0;
}
