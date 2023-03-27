/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_process_4.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:37:57 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/27 08:57:11 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	helper_dq_1(t_x *x)
{
	while (x->str_split[x->i][x->j] != '$')
		x->j++;
	x->var = ft_strchr(x->str_split[x->i], '$');
	if (x->var[ft_strlen(x->var) - 2] == '\''
		|| x->var[ft_strlen(x->var) - 2] == '\"')
	{
		x->var[ft_strlen(x->var) - 2] = '\0';
		x->case_5 = 1;
	}
	else if (x->var[ft_strlen(x->var) - 1] == '\''
		|| x->var[ft_strlen(x->var) - 1] == '\"')
	{
		x->var[ft_strlen(x->var) - 1] = '\0';
		x->case_5 = 1;
	}
	x->new_str = ft_strjoin(x->new_str, "\1\"");
	x->new_str = ft_strjoin(x->new_str, x->var);
	if (x->str_split[x->i] && x->case_5 == 1)
		x->new_str = ft_strjoin(x->new_str, "\"");
	x->i++;
	if (x->str_split[x->i] && ft_strnstr(x->str_split[x->i], "\"", 1)
		&& ft_strnstr(x->str_split[x->i], "\'", 2))
		helper_dq_2(x);
}

void	helper_dq_d(t_x *x)
{
	int	len;

	x->var = ft_strchr(x->str_split[x->i], '$');
	x->var++;
	if (ft_strnstr(x->var, "$", ft_strlen(x->var)))
	{
		x->str_split[x->i] = ft_strtrim(x->str_split[x->i], "\"");
		x->new_str = split_dollar(x->new_str, x->str_split[x->i]);
	}
	else
	{
		len = ft_strlen(x->str_split[x->i]);
		x->var = ft_substr(x->str_split[x->i], 2, len - 2);
		if (x->var[strlen(x->var) - 1] == '"')
			x->var[strlen(x->var) - 1] = '\0';
		x->new_str = simple_v(x->var, x->new_str);
	}
}

void	helper_d(t_x *x)
{
	int	len;

	if (ft_strnstr(x->str_split[x->i], "\"", ft_strlen(x->str_split[x->i])))
	{
		len = ft_strlen(x->str_split[x->i]);
		x->var = ft_substr(x->str_split[x->i], 1, len - 2);
		x->new_str = simple_v(x->var, x->new_str);
	}
	else
	{
		len = ft_strlen(x->str_split[x->i]);
		x->var = ft_substr(x->str_split[x->i], 1, len);
		if (x->case_4 == 1 || x->case_qdq == 1)
			x->new_str = not_v(x->new_str, x->str_split[x->i]);
		else
			x->new_str = simple_v(x->var, x->new_str);
	}
}

void	helper_q_c(t_x *x)
{
	int	len;

	if (ft_strnstr(x->str_split[x->i], "\'", 1)
		&& x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 1] == '\'')
	{
		len = ft_strlen(x->str_split[x->i]);
		x->new_str = not_v(x->new_str, x->str_split[x->i]);
		if (x->str_split[x->i][0] == '\''
			&& ft_strnstr(x->str_split[x->i], "$", len)
				&& x->str_split[x->i][len - 1] == '\'')
			x->case_4 = 0;
		else if (x->case_4 == 0)
			x->case_4 = 1;
		else if (x->case_4 == 1)
			x->case_4 = 0;
	}
	else if (ft_strnstr(x->str_split[x->i], "$", 2)
		&& (ft_strnstr(x->str_split[x->i], "\'", 1)
			|| x->str_split[x->i][ft_strlen(x->str_split[x->i]) - 1] == '\''))
		x->new_str = not_v(x->new_str, x->str_split[x->i]);
}

void	add_cmd_with_fq_or_with_flq(t_x *x)
{
	x->cmd = getenv(x->var);
	if (x->cmd == NULL)
	{
		printf("i have a problem with the cmd man help!! x->case_1\n");
		x->new_str = ft_strjoin(x->new_str, " ");
	}
	else if (x->case_1 == 1)
	{
		x->new_str = ft_strjoin(x->new_str, "\1'");
		x->new_str = ft_strjoin(x->new_str, x->cmd);
		x->new_str = ft_strjoin(x->new_str, " ");
		x->start = 1;
	}
	else
		x->new_str = begin_and_end_with_quote(x->new_str, x->cmd);
	x->j = 0;
}
