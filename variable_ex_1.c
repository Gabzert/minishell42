/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:25:01 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/24 13:32:17 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sis_case_dq(int n, t_x *x)
{
	new_join(x, "\"");
	x->case_dq = n;
}

void	sis_case_q(int n, t_x *x)
{
	new_join(x, "'");
	x->case_q = n;
}

void	simple_variable(char *str, t_x *x)
{
	x->j = x->i + 1;
	while (str[x->j] && str[x->j] != '\'' && str[x->j] != '\"'
		&& str[x->j] != ' ' && str[x->j] != '$')
		x->j++;
	x->j -= x->i;
	x->var = (char *)ft_calloc(x->j + 1, sizeof(char));
	x->var = ft_memcpy(x->var, str + x->i + 1, x->j - 1);
	if (getenv(x->var))
		new_join(x, getenv(x->var));
	else
		new_join(x, " ");
	x->i += x->j - 1;
	free(x->var);
}

void	helper_ex(char *str, t_x *x)
{
	x->var = (char *)calloc(2, sizeof(char));
	*x->var = str[x->i];
	new_join(x, x->var);
	free(x->var);
}

void	helper_no_echo(t_x *x)
{
	char	*new;

	new = ft_strchr(x->str_split[x->i], '$');
	new++;
	free(x->new_str);
	x->new_str = ft_strdup(getenv(new));
	x->i++;
}
