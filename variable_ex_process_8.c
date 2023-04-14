/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_8.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/13 16:10:02 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/14 13:47:00 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	helper_q_c_wa7ed(t_x *x)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while ((x->str_split[x->i][i] && x->str_split[x->i][i] != '\''))
		i++;
	new = ft_substr(x->str_split[x->i], 0, i);
	simple_v(new, x);
	free(new);
	i++;
	while ((x->str_split[x->i][i] && x->str_split[x->i][i] != '\''))
		i++;
	j = i;
	new = ft_substr(x->str_split[x->i], j, i - 1);
	not_v(new, x);
	free(new);
	i++;
	j = i;
	while ((x->str_split[x->i][i]))
		i++;
	new = ft_substr(x->str_split[x->i], j, i - 1);
	simple_v(new, x);
	free(new);
}

void	simple_v_wa7ed(char *var, t_x *x)
{
	char	*new;

	if (getenv(var))
		new_join(x, getenv(var));
	else if (var[0] == '\"' && ft_strlen(var) == 1)
		new_join(x, "\"");
	else
	{
		if (var[0] == '\"' && var[ft_strlen(var) - 1] == '\"')
			simple_v_5ra(var, x);
		else if (ft_strnstr(var, "\"", 1))
			simple_v_5ra_1(var, x);
		else if (var[ft_strlen(var) - 1] == '\"')
			simple_v_5ra_2(var, x);
		else
		{
			new = ft_strtrim(var, "\"");
			new_join(x, new);
			free(new);
		}
	}
	new_join(x, " ");
}

void	check_for_q_and_d_helper_wa7d(t_x *x)
{
	if (x->case_j_q == 2)
		x->case_j_q = 1;
	else if (x->case_j_d == 2)
		x->case_j_d = 1;
}

void	*check_for_q_and_d_helper_tnen(t_x *x)
{
	x->len = ft_strlen(x->str_split[x->begin]);
	if (ft_strnstr(x->str_split[x->begin], "\'", x->len))
		x->case_j_q = 1;
	else if (ft_strnstr(x->str_split[x->begin], "\"", x->len))
		x->case_j_d = 1;
	if (x->case_j_q == 1 || x->case_j_d == 1)
		return (NULL);
	return ((void *) 1);
}

void	check_for_q_and_d(char *str, t_x *x)
{
	if ((ft_strnstr(str, "\"", ft_strlen(str))
			&& ft_strnstr(str, "\'", ft_strlen(str)))
		|| x->case_1 == 1 || x->case_3 == 1 || x->case_f_q == 1)
		return ;
	while (x->str_split[++x->begin])
		if (check_for_q_and_d_helper_tnen(x) == NULL)
			break ;
	x->end = x->begin;
	if (x->str_split[x->end] && x->str_split[x->end + 1])
	{
		while (x->str_split[++x->end])
		{
			x->len = ft_strlen(x->str_split[x->end]);
			if (ft_strnstr(x->str_split[x->end], "\'", x->len))
				x->case_j_q = 2;
			else if (ft_strnstr(x->str_split[x->end], "\"", x->len))
				x->case_j_d = 2;
			if (x->case_j_q == 2 || x->case_j_d == 2)
				break ;
		}
	}
	if (x->case_j_q == 2 || x->case_j_d == 2)
		check_for_q_and_d_helper_wa7d(x);
	else
		x->end = x->begin;
}
