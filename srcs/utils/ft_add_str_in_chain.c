/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_str_in_chain.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: igeorge <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/05 20:38:47 by igeorge           #+#    #+#             */
/*   Updated: 2022/07/05 20:38:47 by igeorge          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_complete_chain(char *new, char *chain, int index_new)
{
	int	i;
	int	j;

	i = 0;
	j = index_new;
	while (chain[i])
		new[j++] = chain[i++];
	return (new);
}

char	*ft_add_str_in_chain(char *new, char *chain, char *str, int index)
{
	int	i;
	int	j;
	int	y;

	i = 0;
	j = 0;
	y = 0;
	while (chain[i])
	{
		if (i == index)
		{
			while (str[y])
				new[j++] = str[y++];
			return (new);
		}
		new[j] = chain[i];
		i++;
		j++;
	}
	return (new);
}
