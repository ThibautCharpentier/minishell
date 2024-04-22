/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.C                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 10:48:50 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/07 10:48:50 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_size_result(unsigned int nbr)
{
	unsigned int	size;

	if (nbr == 0)
		return (1);
	size = 0;
	while (nbr != 0)
	{
		nbr = nbr / 10;
		size++;
	}
	return (size);
}

static void	ft_put_result(char *res, unsigned int nbr)
{
	while (nbr != 0)
	{
		*res = nbr % 10 + 48;
		nbr = nbr / 10;
		res--;
	}
}

char	*ft_itoa(int n)
{
	char			*res;
	unsigned int	nbr;
	unsigned int	size;

	if (n < 0)
	{
		nbr = -n;
		size = ft_size_result(nbr) + 1;
	}
	else
	{
		nbr = n;
		size = ft_size_result(nbr);
	}
	res = malloc(sizeof(char) * size + 1);
	if (!res)
		return (0);
	if (n < 0)
		res[0] = '-';
	res[size] = 0;
	if (n == 0)
		res[0] = 48;
	ft_put_result(res + size - 1, nbr);
	return (res);
}
