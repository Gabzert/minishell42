/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 12:25:01 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/26 14:28:46 by naal-jen         ###   ########.fr       */
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
	if (x->j == 1)
		x->j++;
	x->var = (char *)ft_calloc(x->j + 1, sizeof(char));
	if (str[x->i + 1] == '\0' || str[x->i + 1] == ' '
		|| str[x->i + 1] == '\'' || str[x->i + 1] == '"')
		x->i--;
	x->var = ft_memcpy(x->var, str + x->i + 1, x->j - 1);
	if (getenv(x->var))
		new_join(x, getenv(x->var));
	else if (x->var[0] == '$' && ft_strlen(x->var) == 1)
		new_join(x, x->var);
	else if (x->var[0] == '?' && ft_strlen(x->var) == 1)
		new_join(x, ft_itoa(g_sig.g_exit));
	else if (x->var[0] == '?' && ft_strlen(x->var) > 1)
		exit_status_simple(x);
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

	if (x->str_split[x->i][0] == '$' && ft_strlen(x->str_split[x->i]) == 1)
		new_join(x, "$");
	else
	{
		new = ft_strchr(x->str_split[x->i], '$');
		new++;
		free(x->new_str);
		if (getenv(new))
			x->new_str = ft_strdup(getenv(new));
		else
			x->new_str = ft_strdup(" ");
	}
	x->i++;
}
