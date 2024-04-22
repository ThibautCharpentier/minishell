/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <tcharpen@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 18:19:36 by tcharpen          #+#    #+#             */
/*   Updated: 2022/06/28 18:19:36 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while (*(s1 + i) != 0 || *(s2 + i) != 0)
	{
		if (*(s1 + i) != *(s2 + i))
		{
			return ((unsigned char) *(s1 + i) - (unsigned char) *(s2 + i));
		}
		i++;
	}
	if (ft_strlen(s1) < ft_strlen(s2))
		return (-1);
	else if (ft_strlen(s1) > ft_strlen(s2))
		return (1);
	return (0);
}
