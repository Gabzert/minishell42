/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:36:02 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/01 14:05:41 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_var(t_x *x)
{
	new_join(x, x->var);
	new_join(x, " ");
}

void	add_q_var_c3(t_x *x)
{
	new_join(x, "\1\"");
	new_join(x, x->var);
	new_join(x, " ");
	x->case_3 = 0;
}

void	remove_lase_dq_add_dq(t_x *x)
{
	x->j--;
	x->var[x->j] = '\0';
	if (x->str_split[x->i][0] == '\"')
		new_join(x, "\1\"");
	new_join(x, x->var);
	new_join(x, "\"");
	x->case_3 = 2;
}

void	case_1_helper_0(t_x *x)
{
	if (ft_strnstr(x->str_split[x->i], "\"", 1)
		|| ft_strnstr(x->str_split[x->i], "\"", 2))
		x->case_3 = 3;
	x->var = ft_strchr(x->str_split[x->i], '$');
	x->j = ft_strlen(x->var);
	if (x->var[x->j - 1] == '\"')
		remove_lase_dq_add_dq(x);
	else if (!(x->var[x->j - 1] >= 'A' && x->var[x->j - 1] <= 'Z'))
		clean_var(x);
	if (x->case_3 == 3)
		add_q_var_c3(x);
	else if (x->case_3 != 2)
		add_var(x);
}

void	helper_dq_2(t_x *x)
{
	new_join(x, " ");
	new_join(x, "\1\"");
}
