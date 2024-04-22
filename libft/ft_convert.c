/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_convert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:39:33 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/18 15:39:33 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_convert_char(int c, int *size)
{
	ft_putchar_fd((char) c, 1);
	*size = *size + 1;
}

void	ft_convert_str(char *s, int *size)
{
	int		i;

	if (!s)
	{
		ft_putstr_fd("(null)", 1);
		*size = *size + 6;
	}
	else
	{
		i = -1;
		while (s[++i])
		{
			ft_putchar_fd(s[i], 1);
			*size = *size + 1;
		}
	}
}

void	ft_convert_ptr(unsigned long adr, int *size, char *base)
{
	ft_putstr_fd("0x", 1);
	*size = *size + 2;
	ft_convert_base(adr, size, base);
}

void	ft_convert_int(int n, int *size)
{
	unsigned int	nbr;

	nbr = n;
	if (n < 0)
	{
		ft_putchar_fd('-', 1);
		nbr = -n;
		*size = *size + 1;
	}
	ft_convert_base(nbr, size, "0123456789");
}

void	ft_convert_base(unsigned long nbr, int *size, char *base)
{
	if (nbr >= ft_strlen (base))
	{
		ft_convert_base(nbr / ft_strlen(base), size, base);
		ft_putchar_fd(base[nbr % ft_strlen(base)], 1);
	}
	else
		ft_putchar_fd(base[nbr], 1);
	*size = *size + 1;
}
