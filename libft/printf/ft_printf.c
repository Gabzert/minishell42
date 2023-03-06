/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf->c                                        :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 12:15:26 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/12 12:15:27 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "ft_printf.h"

int	ft_check_flags(char *ptr, t_format *f)
{
	int	i;

	i = 0;
	format_initializer(f);
	while (is_flag(ptr[i]) == 1 && (ptr[i] > '9' || ptr[i] < '1'))
	{
		if (ptr[i] == '0')
			f->zero = 1;
		else if (ptr[i] == ' ')
			f->space = 1;
		else if (ptr[i] == '-')
			f->minus = 1;
		else if (ptr[i] == '+')
			f->plus = 1;
		else if (ptr[i] == '#')
			f->hash = 1;
		i++;
	}
	if (ptr[i] == '.' || (ptr[i] <= '9' && ptr[i] >= '1'))
		i += parsecalc(&ptr[i], f);
	return (i);
}

int	ft_check_specifier(char c, va_list ptr, int *count, t_format *format)
{
	format->spec = c;
	ft_formatter(format);
	if (c == 'd' || c == 'i')
		return (ft_printnum(va_arg(ptr, int), count, format));
	else if (c == 'c')
		return (ft_printchr(va_arg(ptr, int), count, format));
	else if (c == 's')
		return (ft_printstr(va_arg(ptr, char *), count, format));
	else if (c == 'x' || c == 'X')
		return (ft_printhex(va_arg(ptr, unsigned int), c, count, format));
	else if (c == 'u')
		return (ft_printun(va_arg(ptr, unsigned int), count, format));
	else if (c == 'p')
		return (ft_printmem(va_arg(ptr, void *), count, format));
	else if (c == '%')
	{
		write(1, "%", 1);
		*count += 1;
	}
	return (1);
}

int	ft_printf(const char *str, ...)
{
	t_format	format;
	int			i;
	int			count;
	va_list		ptr;

	i = 0;
	count = 0;
	va_start(ptr, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i += ft_check_flags(&((char *)str)[i + 1], &format);
			i += ft_check_specifier(str[i + 1], ptr, &count, &format);
		}
		else
		{
			write(1, &str[i], 1);
			count++;
		}
		i++;
	}
	va_end(ptr);
	return (count);
}
