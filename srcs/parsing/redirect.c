/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 16:56:29 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/06 16:56:29 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*wich_redirect_double(char *parse, int *i, char c, t_com *lst_com)
{
	if (c == '>')
	{
		if (!malloc_path(parse + *i + 2, 2, lst_com))
			return (free_under_tab(parse));
		parse = remalloc_without(parse, i, size_path(parse + *i + 2, 1) + 2);
		*i = -1;
	}
	else if (c == '<')
	{
		if (!malloc_path(parse + *i + 2, 4, lst_com))
			return (free_under_tab(parse));
		parse = remalloc_without(parse, i, size_path(parse + *i + 2, 1) + 2);
		*i = -1;
	}
	return (parse);
}

static char	*wich_redirect_simple(char *parse, int *i, char c, t_com *lst_com)
{
	if (c == '>')
	{
		if (!malloc_path(parse + *i + 1, 1, lst_com))
			return (free_under_tab(parse));
		parse = remalloc_without(parse, i, size_path(parse + *i + 1, 1) + 1);
		*i = -1;
	}
	else if (c == '<')
	{
		if (!malloc_path(parse + *i + 1, 3, lst_com))
			return (free_under_tab(parse));
		parse = remalloc_without(parse, i, size_path(parse + *i + 1, 1) + 1);
		*i = -1;
	}
	return (parse);
}

static	char	*separate_redirect(char *parse, t_com *lst_com)
{
	int	i;

	i = -1;
	while (parse[++i])
	{	
		if (parse[i] == '\'' || parse[i] == '\"')
			skip_quote(parse, parse[i], &i);
		else if ((parse[i] == '>' && parse[i + 1] == '>')
			|| (parse[i] == '<' && parse[i + 1] == '<'))
			parse = wich_redirect_double(parse, &i, parse[i], lst_com);
		else if (parse[i] == '>' || parse[i] == '<')
			parse = wich_redirect_simple(parse, &i, parse[i], lst_com);
		if (!parse)
			return (parse);
	}
	return (parse);
}

int	redirect(char **parse)
{
	int		i;
	t_com	*tmp;

	tmp = g_var.lst_com;
	if (!check_redirect(parse))
		return (syntax_error("syntax error redirect\n"));
	i = 0;
	while (parse[i])
	{
		parse[i] = separate_redirect(parse[i], tmp);
		i++;
		tmp = tmp->next;
	}
	return (1);
}
