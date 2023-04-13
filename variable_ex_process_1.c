/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:24:46 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/13 23:17:17 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_join(t_x *x, char *str)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (x->new_str[i] != '\0')
		i++;
	while (str[j] != '\0')
	{
		x->new_str[i] = str[j];
		i++;
		j++;
	}
	x->new_str[i] = '\0';
}

void	add_command(t_x *x)
{
	char	*new;

	if (ft_strnstr(x->str_split[x->i], "$", ft_strlen(x->str_split[x->i])))
	{
		new = ft_strchr(x->str_split[x->i], '$');
		new++;
		free(x->new_str);
		x->new_str = ft_strdup(getenv(new));
		x->i++;
		return ;
	}
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
	int	j;

	x->i++;
	j = x->i;
	if (x->str_split[x->i])
	{
		while (x->str_split[j])
		{
			len = ft_strlen(x->str_split[j]);
			if (ft_strnstr(x->str_split[j], "\"", len))
			{
				x->case_1 = 1;
				x->i--;
				return ;
			}
			j++;
		}
	}
	if (x->str_split[x->i]
		&& ft_strnstr(x->str_split[x->i], "\"", len))
		x->case_1 = 1;
	else
		x->i--;
}

void	check_for_dq_and_qd(t_x *x)
{
	while (x->str_split[x->i])
	{
		x->len = ft_strlen(x->str_split[x->i]);
		if (ft_strnstr(x->str_split[x->i], "\"", x->len)
			&& (!(ft_strnstr(x->str_split[x->i], "\'", x->len))))
		{
			if (x->case_f_q == 1)
			{
				x->case_qdq = 1;
				return ;
			}
			else
				x->case_q = 1;
		}
		if (ft_strnstr(x->str_split[x->i], "\"", 1))
			check_for_dq_and_qd_helper_2(x);
		else if (ft_strnstr(x->str_split[x->i], "\'", 1))
			check_for_dq_and_qd_helper(x);
		else if (ft_strnstr(x->str_split[x->i], "\'", 1))
			x->case_f_q = 1;
		if (x->case_1 == 1 || x->case_3 == 1)
			break ;
		x->i++;
	}
}

void	add_cmd_q_c3(t_x *x)
{
	x->cmd = getenv(x->var);
	if (!x->cmd)
		free(x->cmd);
	else
	{
		new_join(x, x->cmd);
		new_join(x, "' ");
		x->case_3 = 0;
	}
}
