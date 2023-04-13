/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_7.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:44:25 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/13 17:21:32 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_31_helper(t_x *x)
{
	char	*new;

	while (x->str_split[x->i])
	{
		x->len = ft_strlen(x->str_split[x->i]);
		if (ft_strnstr(x->str_split[x->i], "\'", x->len)
			&& (!(ft_strnstr(x->str_split[x->i], "$", x->len))))
			add_q_s(x);
		else if (ft_strnstr(x->str_split[x->i], "$", x->len))
			case_3_helper(x);
		else if (ft_strnstr(x->str_split[x->i], "\"", x->len) == NULL
			&& ft_strlen(x->str_split[x->i]) != 1)
			case_31_helper_wa7ed(x);
		else if (ft_strnstr(x->str_split[x->i], "\"", 1)
			&& ft_strlen(x->str_split[x->i]) != 1)
		{
			new = ft_strtrim(x->str_split[x->i], "\"");
			new_join(x, new);
			new_join(x, " ");
			free(new);
		}
		x->i++;
	}
}

void	case_11_helper(t_x *x)
{
	x->len = ft_strlen(x->str_split[x->i]);
	while (x->str_split[x->i]
		&& (!((ft_strnstr(x->str_split[x->i], "\"", x->len))
				|| (ft_strnstr(x->str_split[x->i], "\'", x->len)))))
	{
		if (ft_strnstr(x->str_split[x->i], "$", 1))
			case_1_helper(x);
		x->i++;
	}
	while (x->str_split[x->i])
	{
		x->len = ft_strlen(x->str_split[x->i]);
		if (ft_strnstr(x->str_split[x->i], "\"", x->len)
			&& (!(ft_strnstr(x->str_split[x->i], "$", x->len))))
			case_11_helper_tnen(x);
		else if (ft_strnstr(x->str_split[x->i], "$", x->len))
			case_1_helper_0(x);
		else if (ft_strnstr(x->str_split[x->i], "\'", x->len) == NULL
			&& ft_strlen(x->str_split[x->i]) != 1)
			case_11_helper_tlate(x);
		else if (ft_strnstr(x->str_split[x->i], "\'", 1)
			&& ft_strlen(x->str_split[x->i]) != 1)
			case_11_helper_wa7ed(x);
		x->i++;
	}
}

void	helper_1(t_x *x)
{
	if (x->str_split[x->i][x->j] == '$'
		&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 2] == '\''
			&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 1] == '\"')
	{
		end_with_quote(x, x->str_split[x->i]);
		x->i++;
		x->bk = 1;
	}
	else if (x->str_split[x->i][x->j] == '$'
		&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 2] == '\"'
			&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 1] == '\'')
	{
		end_with_dquote(x, x->str_split[x->i]);
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
