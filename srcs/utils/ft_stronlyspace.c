/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stronlyspace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 19:37:37 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/13 19:37:37 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_stronlyspace(char *str)
{
	int	i_str;

	if (!str)
		return (0);
	i_str = -1;
	while (str[++i_str])
	{
		if (str[i_str] != ' ' && str[i_str] != '\f' && str[i_str] != '\n'
			&& str[i_str] != '\r' && str[i_str] != '\t' && str[i_str] != '\v')
			return (0);
	}
	return (1);
}
