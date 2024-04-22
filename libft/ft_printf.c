/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcharpen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 14:24:34 by tcharpen          #+#    #+#             */
/*   Updated: 2021/11/12 14:24:34 by tcharpen         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_put_arg(const char *str, va_list *ap, int *size)
{
	if (*str == 'c')
		ft_convert_char(va_arg(*ap, int), size);
	else if (*str == 's')
		ft_convert_str(va_arg(*ap, char *), size);
	else if (*str == 'p')
		ft_convert_ptr(va_arg(*ap, unsigned long), size, "0123456789abcdef");
	else if (*str == 'd' || *str == 'i')
		ft_convert_int(va_arg(*ap, int), size);
	else if (*str == 'u')
		ft_convert_base(va_arg(*ap, unsigned int), size, "0123456789");
	else if (*str == 'x')
		ft_convert_base(va_arg(*ap, unsigned int), size, "0123456789abcdef");
	else if (*str == 'X')
		ft_convert_base(va_arg(*ap, unsigned int), size, "0123456789ABCDEF");
	else
	{
		ft_putchar_fd(*str, 1);
		*size = *size + 1;
	}
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		size;

	i = -1;
	size = 0;
	va_start(ap, str);
	while (str[++i])
	{
		if (str[i] != '%')
		{
			ft_putchar_fd(str[i], 1);
			size++;
		}
		else if (str[i] == '%' && str[i + 1])
		{
			i++;
			ft_put_arg(str + i, &ap, &size);
		}
	}
	va_end(ap);
	return (size);
}
