/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_5.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:40:14 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/01 14:03:26 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_1_and_dollar_and_quote(t_x *x)
{
	char	*new;
	x->new_split = ft_split(x->var, '\'');
	x->y = 0;
	while (x->new_split[x->y])
	{
		if (ft_strnstr(x->new_split[x->y], "$", 1))
		{
			x->var = x->new_split[x->y];
			new = ft_substr(x->var, 1, ft_strlen(x->var));
		}
		else
			new = x->new_split[x->y];
		if (getenv(new))
		{
			new_join(x, getenv(new));
			new_join(x, "\'");
		}
		free(new);
		x->y++;
	}
}

void	clear_case_1_and_dollar(t_x *x)
{
	x->var = ft_strchr(x->str_split[x->i], '$');
	x->var++;
	x->j = ft_strlen(x->var);
	if (!(x->var[x->j - 1] >= 'A' && x->var[x->j - 1] <= 'Z'))
	{
		while ((!(x->var[x->j - 1] >= 'A' && x->var[x->j - 1] <= 'Z')))
			x->j--;
		x->var[x->j] = '\0';
		x->case_1 = 2;
	}
}

void	dq_with_var(t_x *x)
{
	x->var = ft_strchr(x->str_split[x->i], '$');
	if (x->var[ft_strlen(x->var) - 2] == '\''
		|| x->var[ft_strlen(x->var) - 2] == '\"')
	{
		x->var[ft_strlen(x->var) - 2] = '\0';
		x->case_5 = 1;
	}
	new_join(x, " ");
	new_join(x, x->var);
	if (x->case_5 == 1)
		new_join(x, "\1\"");
	new_join(x, " ");
	new_join(x, " ");
}

void	quote(t_x *x)
{
	x->y = x->j;
	x->y++;
	if (ft_strlen(x->str_split[x->i]) > 2)
	{
		while (x->str_split[x->i][x->y] && x->str_split[x->i][x->y] != '"')
			x->y++;
		x->var = ft_substr(x->str_split[x->i], x->j + 1, x->y - x->j);
		new_join(x, x->var);
		free(x->var);
		if (x->str_split[x->i][x->y] && x->str_split[x->i][x->y + 1])
			x->y++;
		x->j = x->y;
		while (x->str_split[x->i][x->y] && x->str_split[x->i][x->y] != '"')
			x->y++;
		x->var = ft_substr(x->str_split[x->i], x->j, x->y - x->j);
		new_join(x, x->var);
		new_join(x, "\"");
		free(x->var);
	}
}

void	identify_start_dq_q(t_x *x)
{
	new_join(x, "\1\' ");
	x->start = 1;
}
