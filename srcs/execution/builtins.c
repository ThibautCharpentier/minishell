/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:22:14 by tcharpen          #+#    #+#             */
/*   Updated: 2022/07/05 20:22:14 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	run_builtin(t_com *lst_com, int builtin)
{
	if (builtin == B_ECHO)
		run_echo(lst_com);
	else if (builtin == B_CD)
		run_cd(lst_com);
	else if (builtin == B_PWD)
		run_pwd(lst_com);
	else if (builtin == B_EXPORT)
		run_export(lst_com);
	else if (builtin == B_UNSET)
		run_unset(lst_com);
	else if (builtin == B_ENV)
		run_env(lst_com);
	else
		run_exit(lst_com);
	if (g_var.pipe_idx < g_var.nb_pipe)
		close(g_var.pipe[g_var.pipe_idx][1]);
}

int	check_builtins(char *command)
{
	int	i_builtins;

	i_builtins = 0;
	while (g_var.builtins[i_builtins]
		&& !ft_same_str(command, g_var.builtins[i_builtins]))
		i_builtins++;
	return (i_builtins);
}
