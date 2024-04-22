/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 14:19:06 by igeorge           #+#    #+#             */
/*   Updated: 2022/06/10 14:19:06 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	parse_command(char *line)
{
	int		i;

	i = 0;
	while (is_space(line[i]))
		i++;
	if (!separate_by_pipe(line))
		return (0);
	g_var.nb_pipe = g_var.parsing.nbr_command - 1;
	g_var.lst_com = init_command(g_var.parsing.nbr_command);
	put_variable(g_var.parsing.parse);
	if (!redirect(g_var.parsing.parse))
		return (0);
	command_tab(g_var.parsing.parse, g_var.lst_com, g_var.parsing.nbr_command);
	free_doubletab(g_var.parsing.parse);
	g_var.parsing.parse = NULL;
	return (1);
}

int	parse(char *line)
{
	t_com	*tmp;
	int		i_limit;

	if (!count_quote(line))
		return (0);
	if (!parse_command(line))
		return (0);
	tmp = g_var.lst_com;
	while (tmp)
	{
		i_limit = -1;
		while (tmp->limit && tmp->limit[++i_limit])
		{
			free(tmp->str_input);
			tmp->str_input = get_redirection(tmp->limit[i_limit]);
			if (!tmp->str_input)
			{
				free_lst_com(g_var.lst_com);
				return (0);
			}
		}
		tmp = tmp->next;
	}
	return (1);
}
