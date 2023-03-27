/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:24:46 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/26 23:32:12 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_command(t_x *x)
{
	while (x->str_split[x->i][x->j])
	{
		if (x->str_split[x->i][x->j] == '\''
			|| x->str_split[x->i][x->j] == '\"')
			x->j++;
		x->new_str[x->y] = x->str_split[x->i][x->j];
		x->j++;
		x->y++;
	}
	x->new_str[x->y] = ' ';
	x->y++;
	x->new_str[x->y] = '\0';
	x->i++;
	x->j = 0;
}

void	check_for_dq_and_qd_helper(t_x *x)
{
	int	len;

	x->i++;
	if (x->str_split[x->i])
		len = ft_strlen(x->str_split[x->i]);
	if (x->str_split[x->i]
		&& ft_strnstr(x->str_split[x->i], "\"", len))
		x->case_1 = 1;
	else
		x->i--;
}

void	check_for_dq_and_qd(t_x *x)
{
	int	len;

	while (x->str_split[x->i])
	{
		if (ft_strnstr(x->str_split[x->i], "\"", 1))
		{
			x->i++;
			if (x->str_split[x->i])
				len = ft_strlen(x->str_split[x->i]);
			if (x->str_split[x->i]
				&& ft_strnstr(x->str_split[x->i], "\'", len))
				x->case_3 = 1;
			else
				x->i--;
		}
		else if (ft_strnstr(x->str_split[x->i], "\'", 1)
			&& ft_strlen(x->str_split[x->i]) == 1)
			check_for_dq_and_qd_helper(x);
		if (x->case_1 == 1 || x->case_3 == 1)
			break ;
		x->i++;
	}
}

void	add_q_s(t_x *x)
{
	x->new_str = ft_strjoin(x->new_str, "\1'");
	x->new_str = ft_strjoin(x->new_str, " ");
}

void	add_cmd_q_c3(t_x *x)
{
	x->cmd = getenv(x->var);
	if (!x->cmd)
	{
		printf("blabalbla\n");
	}
	else
	{
		x->new_str = ft_strjoin(x->new_str, x->cmd);
		x->new_str = ft_strjoin(x->new_str, "' ");
		x->case_3 = 0;
	}
}
