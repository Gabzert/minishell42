/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/13 14:34:22 by gfantech          #+#    #+#             */
/*   Updated: 2022/10/13 14:34:28 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "../srcs/ft_libft.h"

typedef struct s_format
{
	int		minus;
	int		plus;
	int		space;
	int		hash;
	int		zero;
	int		width;
	int		precision;
	int		pc_check;
	int		di_sign;
	char	spec;
	char	parse;
	int		pnull;
}	t_format;

int		ft_printchr(int c, int *count, t_format *f);
int		ft_printstr(char *str, int *count, t_format *f);
int		ft_printnum(int val, int *count, t_format *f);
int		ft_printhex(unsigned int n, char c, int *count, t_format *f);
int		ft_printun(unsigned int n, int *count, t_format *f);
int		ft_printmem(void *ptr, int *count, t_format *f);
int		ft_printf(const char *str, ...);
int		is_flag(char c);
int		parsecalc(char *str, t_format *format);
void	ft_formatter(t_format *f);
void	format_initializer(t_format *f);
void	ft_printer(t_format *f, char *str, int *count);
char	*res_malloc_num(t_format f, int *len, int is_zero);
void	parsing(t_format *f, int i);

#endif
