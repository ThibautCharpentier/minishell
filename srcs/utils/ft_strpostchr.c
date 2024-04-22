/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpostchr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/11 15:16:01 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/11 15:16:01 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strpostchr(char *str, char c)
{
	size_t	i_str;
	char	*new;
	int		i_new_str;

	if (!str || !ft_strchr(str, c))
	{
		new = malloc(1);
		if (!new)
			return (NULL);
		new[0] = '\0';
		return (new);
	}
	i_str = 0;
	i_new_str = 0;
	while (str[i_str] && str[i_str] != c)
		i_str++;
	i_str++;
	new = malloc(sizeof(char) * (ft_strlen(str) - i_str + 1));
	if (!new)
		return (NULL);
	while (i_str <= ft_strlen(str))
		new[i_new_str++] = str[i_str++];
	return (new);
}
