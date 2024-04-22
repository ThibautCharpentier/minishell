/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/10 17:55:28 by igeorge           #+#    #+#             */
/*   Updated: 2022/06/10 17:55:28 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	skip_quote(char *line, char c, int *i)
{
	if (c == '\'')
		find_pair(line, '\'', i);
	if (c == '\"')
		find_pair(line, '\"', i);
}

int	find_pair(char *str, char pair, int *i)
{
	while (str[*i])
	{
		*i = *i + 1;
		if (str[*i] == pair)
			return (1);
	}
	return (0);
}

int	count_quote(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
		{	
			if (!find_pair(line, '\'', &i))
				return (syntax_error("quotes are not closed\n"));
		}
		else if (line[i] == '\"')
		{
			if (!find_pair(line, '\"', &i))
				return (syntax_error("quotes are not closed\n"));
		}
		i++;
	}
	return (1);
}
