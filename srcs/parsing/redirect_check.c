/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_check.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 16:22:46 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/07 16:22:46 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	is_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}

static	int	word_after(char *parse)
{
	int	i;

	i = 1;
	while (parse[i])
	{
		if (is_redirect(parse[i]))
			return (0);
		else if (is_space(parse[i]))
			i++;
		else
			return (1);
	}
	return (0);
}

static int	check_line(char *parse)
{
	int	i;

	i = 0;
	while (parse[i])
	{
		if (parse[i] == '\'' || parse[i] == '\"')
			skip_quote(parse, parse[i], &i);
		else if (is_redirect(parse[i]))
		{
			if (parse[i + 1] && is_redirect(parse[i + 1]))
				i++;
			if (!word_after(parse + i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	check_redirect(char **parse)
{
	int	i;

	i = 0;
	while (parse[i])
	{
		if (!check_line(parse[i]))
			return (0);
		i++;
	}
	return (1);
}
