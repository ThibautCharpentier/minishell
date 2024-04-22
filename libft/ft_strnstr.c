/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/04 16:08:44 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/04 16:08:44 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *s1, const char *s2, size_t len)
{
	char	*str1;
	char	*str2;
	size_t	i;
	size_t	n;

	i = 0;
	str1 = (char *) s1;
	str2 = (char *) s2;
	if (!*str2)
		return (str1);
	while (str1[i] && i < len)
	{
		n = 0;
		while (str1[i + n] && str2[n] && str1[i + n] == str2[n] && i + n < len)
			n++;
		if (!str2[n])
			return (str1 + i);
		i++;
	}
	return (0);
}
