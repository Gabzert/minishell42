/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:33:36 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/27 10:04:51 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	begin_w_q_c3(t_x *x)
{
	x->new_str = begin_with_quote(x->new_str, x->var);
	x->case_3 = 0;
}

void	clean_var(t_x *x)
{
	while ((!(x->var[x->j - 1] >= 'A' && x->var[x->j - 1] <= 'Z')))
		x->j--;
	x->var[x->j] = '\0';
}

void	remove_last_q_add_q(t_x *x)
{
	x->j--;
	x->var[x->j] = '\0';
	x->cmd = getenv(x->var);
	if (!x->cmd)
		free(x->cmd);
	if (x->str_split[x->i][0] == '\'')
		x->new_str = ft_strjoin(x->new_str, "\1\'");
	x->new_str = ft_strjoin(x->new_str, x->cmd);
	x->new_str = ft_strjoin(x->new_str, "\'");
	x->case_3 = 4;
}

void	case_3_helper(t_x *x)
{
	int	len;

	len = ft_strlen(x->str_split[x->i]);
	if (ft_strnstr(x->str_split[x->i], "\'", 1)
		|| ft_strnstr(x->str_split[x->i], "\'", 2))
		x->case_3 = 3;
	else if (ft_strnstr(x->str_split[x->i], "$", len)
		&& (ft_strnstr(x->str_split[x->i], "\'", len - 1)
			|| ft_strnstr(x->str_split[x->i], "\'", len - 2)))
		x->case_3 = 6;
	x->var = ft_strchr(x->str_split[x->i], '$');
	x->var++;
	x->j = ft_strlen(x->var);
	if (x->var[x->j - 1] == '\'')
		remove_last_q_add_q(x);
	else if (!(x->var[x->j - 1] >= 'A' && x->var[x->j - 1] <= 'Z'))
		clean_var(x);
	if (x->case_3 != 4 && x->case_3 != 3 && x->case_3 != 6)
		x->new_str = simple_v(x->var, x->new_str);
	else if (x->case_3 == 3)
		begin_w_q_c3(x);
	else if (x->case_3 == 6)
		add_cmd_q_c3(x);
}

void	case_1_helper(t_x *x)
{
	x->var = ft_strchr(x->str_split[x->i], '$');
	x->var++;
	x->cmd = getenv(x->var);
	if (!x->cmd)
		free(x->cmd);
	else
	{
		x->new_str = ft_strjoin(x->new_str, x->cmd);
		x->new_str = ft_strjoin(x->new_str, " ");
	}
}
