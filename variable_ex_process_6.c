/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_6.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:42:46 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/01 13:35:07 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	identify_end_dq_q(t_x *x)
{
	new_join(x, "\1\' ");
	x->start = 0;
}

void	identify_start_q_dq(t_x *x)
{
	new_join(x, "\1\" ");
	x->start = 1;
	x->case_qdq = 1;
}

void	identify_end_q_dq(t_x *x)
{
	new_join(x, "\1\" ");
	x->start = 0;
	x->case_qdq = 0;
}

void	identify(t_x *x)
{
	if (x->start == 0 && ft_strlen(x->str_split[x->i]) == 2
		&& x->str_split[x->i][x->j] == '\"'
			&& x->str_split[x->i][x->j + 1] == '\'')
		identify_start_dq_q(x);
	else if (x->start == 1 && ft_strlen(x->str_split[x->i]) == 2
		&& x->str_split[x->i][x->j] == '\''
			&& x->str_split[x->i][x->j + 1] == '\"')
		identify_end_dq_q(x);
	else if (x->start == 0 && ft_strlen(x->str_split[x->i]) == 2
		&& x->str_split[x->i][x->j] == '\''
			&& x->str_split[x->i][x->j + 1] == '\"')
		identify_start_q_dq(x);
	else if (x->start == 1 && ft_strlen(x->str_split[x->i]) == 2
		&& x->str_split[x->i][x->j] == '\"'
			&& x->str_split[x->i][x->j + 1] == '\'')
		identify_end_q_dq(x);
}

void	helper_dq_var(t_x *x)
{
	while (x->str_split[x->i])
	{
		if (ft_strnstr(x->str_split[x->i], "$", 1))
			dq_with_var(x);
		x->i++;
	}
}
