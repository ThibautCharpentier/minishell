/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strprechr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 21:32:44 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/11 21:32:44 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strprechr(char *str, char c)
{
	int		i_str;
	char	*new;

	if (!str)
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	i_str = 0;
	while (str[i_str] && str[i_str] != c)
		i_str++;
	new = malloc(sizeof(char) * (i_str + 1));
	if (!new)
		return (NULL);
	new[i_str] = '\0';
	while (--i_str > -1)
		new[i_str] = str[i_str];
	return (new);
}
