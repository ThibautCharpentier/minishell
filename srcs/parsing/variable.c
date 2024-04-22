/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 14:56:12 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/01 14:56:12 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*parse_variable(char *str)
{
	int		size;
	int		i;
	char	*variable;

	i = 0;
	size = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '_'))
	{
		size++;
		i++;
	}
	variable = malloc(sizeof(char) * (size + 1));
	if (!variable)
		free_all(1, "malloc");
	variable[size] = '\0';
	i = 0;
	while (str[i] && (ft_isalpha(str[i]) || ft_isdigit(str[i])
			|| str[i] == '_'))
	{
		variable[i] = str[i];
		i++;
	}
	return (variable);
}

static char	*find_value(char *str, t_env *lst_env)
{
	t_env	*tmp;

	tmp = lst_env;
	while (tmp)
	{
		if (ft_same_str(str, tmp->key))
			return (tmp->value);
		else
			tmp = tmp->next;
	}
	return (NULL);
}

static char	*variable_replace(char *i_parse, char *parse, int *index)
{
	int		i;
	char	*variable;
	char	*value;

	i = 1;
	if (ft_isdigit(i_parse[i]))
		parse = remalloc_without(parse, index, 2);
	else if (i_parse[i] == '?')
		parse = remalloc_lastexit(parse, index);
	else if ((!ft_isalpha(i_parse[i]) && i_parse[i] != '_'))
		parse = remalloc_without(parse, index, 1);
	else
	{
		variable = parse_variable(i_parse + i);
		value = find_value(variable, g_var.lst_env);
		if (value)
			parse = remalloc_with_var(parse, variable, value, index);
		else
			parse = remalloc_without(parse, index, ft_strlen(variable) + 1);
		free(variable);
	}
	return (parse);
}

static char	*str_variable(char *str_parse)
{
	int	i;
	int	double_quote;

	i = 0;
	double_quote = 0;
	while (str_parse[i])
	{
		if (str_parse[i] == '\'' && double_quote == 0)
			skip_quote(str_parse, str_parse[i], &i);
		else if (str_parse[i] == '\"' && double_quote == 0)
			double_quote = 1;
		else if (str_parse[i] == '\"' && double_quote == 1)
			double_quote = 0;
		else if (str_parse[i] == '$' && str_parse[i + 1]
			&& !is_space(str_parse[i + 1]))
		{
			str_parse = variable_replace(str_parse + i, str_parse, &i);
			continue ;
		}
		i++;
	}
	return (str_parse);
}

void	put_variable(char **parse)
{
	int	i;

	i = 0;
	while (parse[i])
	{
		parse[i] = str_variable(parse[i]);
		i++;
	}
}
