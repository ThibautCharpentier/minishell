/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:38:39 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/06 13:38:42 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (*(s1 + i) != 0 || *(s2 + i) != 0))
	{
		if (*(s1 + i) != *(s2 + i))
		{
			return ((unsigned char) *(s1 + i) - (unsigned char) *(s2 + i));
		}
		i++;
	}
	return (0);
}
