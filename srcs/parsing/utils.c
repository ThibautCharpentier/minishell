/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 13:39:01 by igeorge           #+#    #+#             */
/*   Updated: 2022/06/11 13:39:01 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	wich_quote(char *line, int *i, int quote)
{
	if (line[*i] == '\"')
		find_pair(line, '\"', i);
	else if (line[*i] == '\'')
		find_pair(line, '\'', i);
	quote = quote + 2;
	return (quote);
}

int	size_path(char *line, int space)
{
	int	i;
	int	begin_word;
	int	quote;

	i = 0;
	quote = 0;
	while (is_space(line[i]))
		i++;
	begin_word = i;
	while (line[i])
	{
		if (line[i] == '\"' || line[i] == '\'')
			quote = wich_quote(line, &i, quote);
		else if (is_space(line[i]) || line[i] == '<' || line[i] == '>')
			break ;
		i++;
	}
	if (space == 1)
		return (i);
	return (i - begin_word - quote);
}

int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

int	strlen_c(char *line, char c)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != c)
	{
		if (line[i] == '\'' || line[i] == '\"')
			skip_quote(line, line[i], &i);
		i++;
	}
	return (i);
}
