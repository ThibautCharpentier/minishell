/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 13:08:15 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/06 13:08:18 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (*(dst + i) != 0 && i < dstsize)
		i++;
	if (i == dstsize)
		return (dstsize + ft_strlen(src));
	while (*(src + j) != 0 && j < dstsize - i - 1)
	{
		*(dst + i + j) = *(src + j);
		j++;
	}
	*(dst + i + j) = 0;
	return (i + ft_strlen(src));
}
