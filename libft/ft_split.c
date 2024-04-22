/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/06 16:08:00 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/08 12:52:02 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static unsigned int	ft_size_result(char const *str, char c)
{
	unsigned int	size;
	unsigned int	i;

	i = 0;
	size = 1;
	if (!str[i])
		return (0);
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] && str[i + 1] != c)
			size++;
		i++;
	}
	return (size);
}

static unsigned int	ft_size_str(char const *str, char c)
{
	unsigned int	size;

	size = 0;
	while (str[size] && str[size] != c)
		size++;
	return (size);
}

static void	ft_put_str(char *result, char const *str, unsigned int size)
{
	unsigned int	i;

	i = 0;
	while (i < size)
	{
		*(result + i) = str[i];
		i++;
	}
	*(result + i) = 0;
}

static char	**ft_free_split(char **result, int j)
{
	int	i;

	i = 0;
	while (i < j)
		free(result[i++]);
	free(result);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char			**result;
	int				i;
	unsigned int	j;

	if (!s)
		return (0);
	result = malloc((ft_size_result(s, c) + 1) * sizeof(char *));
	if (!result)
		return (0);
	i = -1;
	j = 0;
	while (s[++i])
	{
		if (ft_size_str(s + i, c) == 0)
			continue ;
		result[j] = malloc((ft_size_str(s + i, c) + 1) * sizeof(char));
		if (!result[j])
			return (ft_free_split(result, j));
		ft_put_str(result[j], s + i, ft_size_str(s + i, c));
		i += ft_size_str(s + i, c) - 1;
		j++;
	}
	result[j] = 0;
	return (result);
}
