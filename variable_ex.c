/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:55:54 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/13 16:16:21 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	simple_v_helper(char *new, t_x *x)
{
	if (getenv(new))
	{
		new_join(x, getenv(new));
		new_join(x, " ");
	}
	else
	{
		free(new);
		return (0);
	}
	return (1);
}

void	helper_4(t_x *x)
{
	while (x->str_split[x->i][x->j])
	{
		helper_1(x);
		if (x->bk == 1)
			break ;
		identify(x);
		if (x->str_split[x->i][x->j] == '\"' && x->case_2 != 1)
			helper_2(x);
		else if (x->str_split[x->i][x->j] == '\'')
			helper_3(x);
		if (x->str_split[x->i] == NULL)
			x->bk = 2;
		if (x->bk == 1 || x->bk == 2)
			break ;
		x->j++;
	}
}

void	helper_5(t_x *x)
{
	helper_4(x);
	if (x->bk == 1)
		x->bk = 0;
	if (x->bk == 2)
		return ;
	x->j = 0;
	if (x->str_split[x->i] && x->case_1
		&& ft_strnstr(x->str_split[x->i], "$", ft_strlen(x->str_split[x->i])))
	{
		clear_case_1_and_dollar(x);
		if (ft_strnstr(x->var, "\'", ft_strlen(x->var)))
		{
			case_1_and_dollar_and_quote(x);
			x->bk = 1;
			return ;
		}
		add_cmd_with_fq_or_with_flq(x);
	}
}

void	helper_6(t_x *x)
{
	if (ft_strnstr(x->str_split[x->i], "\"", ft_strlen(x->str_split[x->i]))
		&& ft_strnstr(x->str_split[x->i], "\'", ft_strlen(x->str_split[x->i])))
	{
		helper_5(x);
		if (x->bk == 2)
			return ;
		if (x->bk == 1)
			return ;
	}
	else if (x->str_split[x->i]
		&& ft_strnstr(x->str_split[x->i], "\'", ft_strlen(x->str_split[x->i])))
		helper_q_c(x);
	else if (x->str_split[x->i] && ft_strnstr(x->str_split[x->i], "$", 1))
		helper_d(x);
	else if (x->str_split[x->i] && ft_strnstr(x->str_split[x->i], "\"", 1)
		&& ft_strnstr(x->str_split[x->i], "$", 2))
		simple_v(x->str_split[x->i], x);
	else if (x->case_q == 1)
		simple_v(x->str_split[x->i], x);
	else if (x->str_split[x->i])
		not_v(x->str_split[x->i], x);
}

char	*control_ex(t_x *x, char *str)
{
	init(x);
	x->size_for_malloc = full_size(str);
	x->str_split = ft_split(str, ' ');
	x->new_str = (char *)malloc(sizeof(char) * (x->size_for_malloc + 1000));
	add_command(x);
	check_for_dq_and_qd(x);
	check_for_q_and_d(str, x);
	x->i = 1;
	if (x->case_3 == 1)
		case_31_helper(x);
	else if (x->case_1 == 1)
		case_11_helper(x);
	while (x->str_split[x->i])
	{
		helper_6(x);
		if (x->bk == 2)
			return (x->new_str);
		if (x->bk == 1 || x->str_split[x->i] == NULL)
			break ;
		x->i++;
	}
	return (x->new_str);
}
