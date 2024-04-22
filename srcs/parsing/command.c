/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/10 17:43:55 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/10 17:43:55 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_nbr_word(char *parse)
{
	int	i;
	int	nbr_word;

	i = 0;
	nbr_word = 0;
	while (parse[i])
	{
		while (parse[i] && is_space(parse[i]))
			i++;
		if (parse[i] && !is_space(parse[i]))
		{
			nbr_word++;
			while (parse[i] && !is_space(parse[i]))
			{
				if (parse[i] == '\'' || parse[i] == '\"')
					skip_quote(parse, parse[i], &i);
				i++;
			}
		}
	}
	return (nbr_word);
}

static	char	*fill_command(char *parse, char *command)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = '0';
	while (parse[i] && is_space(parse[i]))
			i++;
	while (parse[i])
	{
		if (is_space(parse[i]) && quote == '0')
			break ;
		else if ((parse[i] == '\'' || parse[i] == '\"') && quote == '0')
			quote = parse[i];
		else if ((parse[i] == '\'' || parse[i] == '\"') && quote == parse[i])
			quote = '0';
		else
			command[j++] = parse[i];
		i++;
	}
	return (command);
}

static char	**create_under_command(char *parse, char **command, int nbr_word)
{
	int		size;
	int		i;
	int		i_parse;

	i = 0;
	i_parse = 0;
	while (i < nbr_word)
	{
		size = size_word(parse + i_parse, 0);
		command[i] = malloc(sizeof(char) * (size + 1));
		if (!command)
			free_all(1, "malloc");
		command[i][size] = '\0';
		command[i] = fill_command(parse + i_parse, command[i]);
		i_parse = i_parse + size_word(parse + i_parse, 1);
		i++;
	}
	return (command);
}

static char	**create_command(char *parse)
{
	int		size;
	char	**command;

	size = count_nbr_word(parse);
	command = malloc(sizeof(char *) * (size + 1));
	if (!command)
		free_all(1, "malloc");
	command[size] = NULL;
	command = create_under_command(parse, command, size);
	return (command);
}

void	command_tab(char **parse, t_com *lst_com, int nbr_command)
{
	int		i;
	t_com	*tmp;

	i = 0;
	tmp = lst_com;
	while (i < nbr_command)
	{
		if (parse[i])
			tmp->command = create_command(parse[i]);
		i++;
		tmp = tmp->next;
	}
}
