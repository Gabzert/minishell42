/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/16 11:55:54 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/24 13:31:03 by naal-jen         ###   ########.fr       */
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

void	init(t_x *x)
{
	x->i = 0;
	x->j = 0;
	x->y = 0;
	x->case_q = 0;
	x->case_dq = 0;
	x->var = NULL;
	x->str_split = NULL;
	x->new_str = NULL;
}

int	full_size(char *str)
{
	t_size	size;

	size.i = -1;
	size.size_cmd = 0;
	size.size_full = ft_strlen(str);
	while (str[++size.i])
	{
		if (str[size.i] == '$')
		{
			size.j = full_size_helper(str, size.i, size.j);
			size.var = ft_substr(str, size.i + 1, size.j - size.i);
			size.size_full -= ft_strlen(size.var) + 1;
			if (getenv(size.var))
				size.size_cmd += ft_strlen(getenv(size.var));
			else
				size.size_full += ft_strlen(size.var) + 1;
			size.i = size.j - 1;
			size.j = 0;
			free(size.var);
		}
		if ((!(str[size.i] || str[size.i + 1])))
			break ;
	}
	size.size_cmd += size.size_full;
	return (size.size_cmd + 2);
}

void	add_command(char *str, t_x *x)
{
	x->str_split = ft_split(str, ' ');
	if (ft_strnstr(x->str_split[x->i], "$", ft_strlen(x->str_split[x->i])))
	{
		helper_no_echo(x);
		return ;
	}
	while (x->str_split[0][x->i])
	{
		if (x->str_split[0][x->i] == '\"' && x->case_dq == 0 && x->case_q != 1)
			x->case_dq = 1;
		else if (x->str_split[0][x->i] == '\"' && x->case_dq == 1)
			x->case_dq = 0;
		else if (x->str_split[0][x->i] == '\'' && x->case_q == 0
			&& x->case_dq != 1)
			x->case_q = 1;
		else if (x->str_split[0][x->i] == '\'' && x->case_q == 1)
			x->case_q = 0;
		else if (x->str_split[0][x->i] == '\'' && x->case_dq == 1)
			new_join(x, "'");
		else
			helper_ex(x->str_split[0], x);
		x->i++;
	}
}

char	*control_ex(t_x *x, char *str)
{
	init(x);
	x->new_str = (char *)ft_calloc((full_size(str) + 1000), sizeof(char));
	add_command(str, x);
	x->i = ft_strlen(x->str_split[0]);
	while (str[x->i])
	{
		if (str[x->i] == '\"' && x->case_dq == 0 && x->case_q != 1)
			sis_case_dq(1, x);
		else if (str[x->i] == '\"' && x->case_dq == 1)
			sis_case_dq(0, x);
		else if (str[x->i] == '\'' && x->case_q == 0 && x->case_dq != 1)
			sis_case_q(1, x);
		else if (str[x->i] == '\'' && x->case_q == 1)
			sis_case_q(0, x);
		else if (str[x->i] == '$' && x->case_q == 0)
			simple_variable(str, x);
		else if (str[x->i] == ' ')
			new_join(x, " ");
		else if (str[x->i] == '\'' && x->case_dq == 1)
			new_join(x, "'");
		else
			helper_ex(str, x);
		x->i++;
	}
	return (x->new_str);
}
