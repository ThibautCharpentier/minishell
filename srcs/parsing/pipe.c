/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/25 17:12:33 by igeorge           #+#    #+#             */
/*   Updated: 2022/06/25 17:12:33 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	check_pipe(char *line, int *i)
{
	int	j;

	j = *i;
	while (j-- >= 0)
	{
		if (j < 0 || line[j] == '|')
			return (0);
		else if (is_space(line[j]))
			continue ;
		else
			break ;
	}
	*i = *i + 1;
	while (line[*i])
	{
		if (is_space(line[*i]))
			*i = *i + 1;
		else if (line[*i] == '|')
			return (0);
		else
			return (1);
	}
	return (0);
}

static int	count_pipe(char *line)
{
	int	i;

	i = 0;
	g_var.parsing.nbr_command = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
		{
			skip_quote(line, line[i], &i);
			i++;
		}
		else if (line[i] == '|')
		{
			if (!check_pipe(line, &i))
				return (syntax_error("syntax error '|'\n"));
			else
				g_var.parsing.nbr_command++;
		}
		else
			i++;
	}
	g_var.parsing.nbr_command++;
	return (1);
}

static void	fill_str_pipe(char **parse, char *line)
{
	int	size;
	int	i;
	int	j;
	int	index;

	i = 0;
	j = 0;
	while (j < g_var.parsing.nbr_command)
	{
		size = strlen_c(line + i, '|');
		parse[j] = malloc(sizeof(char) * (size + 1));
		if (!parse[j])
			free_all(1, "malloc");
		parse[j][size] = '\0';
		index = -1;
		while (++index < size)
			parse[j][index] = line[i++];
		j++;
		i++ ;
	}
}

int	separate_by_pipe(char *line)
{
	int	nbr_com;

	if (!count_pipe(line))
		return (0);
	nbr_com = g_var.parsing.nbr_command;
	g_var.parsing.parse = malloc(sizeof(char *) * (nbr_com + 1));
	if (!g_var.parsing.parse)
		free_all(1, "malloc");
	g_var.parsing.parse[nbr_com] = NULL;
	fill_str_pipe(g_var.parsing.parse, line);
	return (1);
}
