/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_10.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 12:23:30 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/14 12:32:31 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	simple_v_5ra_1(char *var, t_x *x)
{
	char	*new;

	new = ft_strtrim(var, "\"");
	new_join(x, "\"");
	new_join(x, new);
	free(new);
}

void	simple_v_5ra_2(char *var, t_x *x)
{
	char	*new;

	new = ft_strtrim(var, "\"");
	new_join(x, new);
	new_join(x, "\"");
	free(new);
}

void	helper_q_c_helper(t_x *x)
{
	x->len = ft_strlen(x->str_split[x->i]);
	not_v(x->str_split[x->i], x);
	if (x->str_split[x->i][0] == '\''
		&& ft_strnstr(x->str_split[x->i], "$", x->len)
			&& x->str_split[x->i][x->len - 1] == '\'')
		x->case_4 = 0;
	else if (x->case_4 == 0)
		x->case_4 = 1;
	else if (x->case_4 == 1)
		x->case_4 = 0;
}
