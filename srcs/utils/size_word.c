/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size_word.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 17:24:54 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/08 17:24:54 by igeorge          ###   ########lyon.fr   */
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

int	size_word(char *line, int space)
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
		else if (is_space(line[i]))
			break ;
		i++;
	}
	if (space == 1)
		return (i);
	return (i - begin_word - quote);
}
