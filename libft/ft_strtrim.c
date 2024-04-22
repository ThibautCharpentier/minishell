/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:12:38 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/05 14:12:38 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_findchar(char c, char const *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (c == str[i])
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	start = 0;
	if (!s1)
		return (0);
	while (s1[start] && ft_findchar(s1[start], set))
		start++;
	end = ft_strlen(s1) - 1;
	while (end > start && ft_findchar(s1[end], set))
		end--;
	if (end >= start)
		str = malloc(sizeof(char) * (end - start + 2));
	else
		str = malloc(sizeof(char));
	if (!str)
		return (0);
	i = 0;
	while (start <= end)
		str[i++] = s1[start++];
	str[i] = 0;
	return (str);
}
