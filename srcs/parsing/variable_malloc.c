/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_malloc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 18:35:37 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/01 18:35:37 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*remalloc_without(char *parse, int *index, int size_delete)
{
	int		size;
	int		i;
	int		j;
	char	*new_str;

	size = ft_strlen(parse) - size_delete;
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
		free_all(1, "malloc");
	new_str[size] = '\0';
	i = 0;
	j = 0;
	while (parse[i])
	{
		if (i == *index)
		{
			i = i + size_delete;
			continue ;
		}
		new_str[j] = parse[i];
		i++;
		j++;
	}
	free(parse);
	return (new_str);
}

char	*remalloc_lastexit(char *parse, int *index)
{
	char	*last_exit;
	char	*new_str;
	int		size;
	int		new_i;

	last_exit = ft_itoa(g_var.last_exit);
	if (!last_exit)
		free_all(1, "malloc");
	size = ft_strlen(last_exit) + ft_strlen(parse) - 2;
	new_str = malloc(sizeof(char) * (size + 1));
	if (!new_str)
	{	
		free(last_exit);
		free_all(1, "malloc");
	}
	new_str[size] = '\0';
	new_str = ft_add_str_in_chain(new_str, parse, last_exit, *index);
	new_i = ft_strlen(last_exit) + *index;
	new_str = ft_complete_chain(new_str, parse + *index + 2, new_i);
	free(parse);
	*index = *index + ft_strlen(last_exit);
	free(last_exit);
	return (new_str);
}

char	*remalloc_with_var(char *parse, char *var, char *value, int *index)
{
	char	*new_str;
	int		size;
	int		new_i;
	int		parse_i;

	size = ft_strlen(parse) + ft_strlen(value) - ft_strlen(var) - 1;
	new_str = malloc(sizeof(char) * size + 1);
	if (!new_str)
	{
		free(var);
		free_all(1, "malloc");
	}
	new_str[size] = '\0';
	new_str = ft_add_str_in_chain(new_str, parse, value, *index);
	new_i = *index + ft_strlen(value);
	parse_i = ft_strlen(var) + *index + 1;
	new_str = ft_complete_chain(new_str, parse + parse_i, new_i);
	*index = *index + ft_strlen(value);
	free(parse);
	return (new_str);
}
