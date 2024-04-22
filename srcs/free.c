/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:43:32 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/11 13:43:32 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lst_com(t_com *lst)
{
	t_com	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		if (tmp->fd_read != 0)
			close(tmp->fd_read);
		if (tmp->fd_write != 1)
			close(tmp->fd_write);
		free_tabstr(tmp->command, 0);
		free_tabstr(tmp->limit, 0);
		free(tmp->str_input);
		free(tmp);
	}
	g_var.lst_com = NULL;
}

void	free_lst_env(t_env *lst, int error)
{
	t_env	*tmp;

	while (lst)
	{
		tmp = lst;
		lst = lst->next;
		free(tmp->key);
		free(tmp->value);
		free(tmp);
	}
	g_var.lst_env = NULL;
	if (error)
		malloc_error();
}

void	free_tabstr(char **tabstr, int error)
{
	int	i_tab;

	i_tab = -1;
	if (tabstr)
	{
		while (tabstr[++i_tab])
			free(tabstr[i_tab]);
		free(tabstr);
	}
	tabstr = NULL;
	if (error)
		malloc_error();
}

void	free_pipe(int **pipe)
{
	int	i_pipe;

	i_pipe = -1;
	if (pipe)
	{
		while (++i_pipe < g_var.nb_pipe)
		{
			close(pipe[i_pipe][0]);
			close(pipe[i_pipe][1]);
			free(pipe[i_pipe]);
		}
		free(pipe);
	}
	g_var.pipe = NULL;
}

void	free_all(int error, char *str_error)
{
	free_lst_env(g_var.lst_env, 0);
	free_tabstr(g_var.path, 0);
	free_tabstr(g_var.builtins, 0);
	free_pipe(g_var.pipe);
	free_lst_com(g_var.lst_com);
	if (g_var.line)
		free(g_var.line);
	if (g_var.parsing.parse)
		free_doubletab(g_var.parsing.parse);
	if (g_var.parsing.path)
		free(g_var.parsing.path);
	if (error == 1)
	{
		perror(str_error);
		exit(EXIT_FAILURE);
	}
	exit(g_var.last_exit);
}
