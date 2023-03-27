/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_7.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:44:25 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/27 08:57:50 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_31_helper(t_x *x)
{
	int	len;

	while (x->str_split[x->i])
	{
		len = ft_strlen(x->str_split[x->i]);
		if (ft_strnstr(x->str_split[x->i], "\'", len)
			&& (!(ft_strnstr(x->str_split[x->i], "$", len))))
			add_q_s(x);
		else if (ft_strnstr(x->str_split[x->i], "$", len))
			case_3_helper(x);
		x->i++;
	}
}

void	case_11_helper(t_x *x)
{
	int	len;

	len = ft_strlen(x->str_split[x->i]);
	while (x->str_split[x->i] && (!((ft_strnstr(x->str_split[x->i], "\"", len))
				|| (ft_strnstr(x->str_split[x->i], "\'", len)))))
	{
		if (ft_strnstr(x->str_split[x->i], "$", 1))
			case_1_helper(x);
		x->i++;
	}
	while (x->str_split[x->i])
	{
		len = ft_strlen(x->str_split[x->i]);
		if (ft_strnstr(x->str_split[x->i], "\"", len)
			&& (!(ft_strnstr(x->str_split[x->i], "$", len))))
		{
			x->new_str = ft_strjoin(x->new_str, "\1\"");
			x->new_str = ft_strjoin(x->new_str, " ");
		}
		else if (ft_strnstr(x->str_split[x->i], "$", len))
			case_1_helper_0(x);
		x->i++;
	}
}

void	helper_1(t_x *x)
{
	if (x->str_split[x->i][x->j] == '$'
		&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 2] == '\''
			&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 1] == '\"')
	{
		x->new_str = end_with_quote(x->new_str, x->str_split[x->i]);
		x->i++;
		x->bk = 1;
	}
	else if (x->str_split[x->i][x->j] == '$'
		&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 2] == '\"'
			&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 1] == '\'')
	{
		x->new_str = end_with_dquote(x->new_str, x->str_split[x->i]);
		x->i++;
		x->bk = 1;
	}
}

void	helper_2(t_x *x)
{
	if (ft_strnstr(x->str_split[x->i], "\'", ft_strlen(x->str_split[x->i])))
		x->case_1 = 1;
	x->bk = 1;
}

void	helper_3(t_x *x)
{
	if (x->str_split[x->i][x->j + 1] != '"')
	{
		quote(x);
		x->bk = 1;
	}
	if (x->bk == 1)
		return ;
	x->case_2 = 1;
	x->j++;
	if ((x->str_split[x->i][x->j] == '\"' && strlen(x->str_split[x->i]) > 2))
	{
		helper_dq_1(x);
		if (x->str_split[x->i])
		{
			helper_dq_var(x);
			x->i--;
			x->bk = 1;
		}
	}
}