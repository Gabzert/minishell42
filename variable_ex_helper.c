/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:12:16 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/14 14:30:35 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_for_dq_and_qd_helper_2(t_x *x)
{
	int	j;

	x->i++;
	j = x->i;
	if (x->str_split[x->i])
	{
		while (x->str_split[j])
		{
			x->len = ft_strlen(x->str_split[j]);
			if (ft_strnstr(x->str_split[j], "\'", x->len))
			{
				x->case_3 = 1;
				x->i--;
				return ;
			}
			j++;
		}
	}
	if (x->str_split[x->i]
		&& ft_strnstr(x->str_split[x->i], "\'", x->len))
		x->case_3 = 1;
	else
		x->i--;
}

void	begin_and_end_with_quote(char *cmd, t_x *x)
{
	new_join(x, "\1'");
	new_join(x, cmd);
	new_join(x, "'");
}

void	begin_with_quote(t_x *x, char *var)
{
	char	*new;

	new = ft_strtrim(var, "\'$");
	if (getenv(new))
	{
		new_join(x, "\"\'");
		new_join(x, getenv(new));
		new_join(x, " ");
	}
	free(new);
}

void	end_with_quote(t_x *x, char *str)
{
	char	*var;
	char	*new;
	char	*cmd;

	new = ft_strtrim(str, "\'\"");
	var = ft_strchr(new, '$');
	var++;
	cmd = getenv(var);
	if (cmd == NULL)
		free(cmd);
	else
	{
		new_join(x, cmd);
		new_join(x, "'");
	}
	free(new);
}

void	end_with_dquote(t_x *x, char *str)
{
	char	*var;
	char	*new;

	new = ft_strtrim(str, "\'\"");
	var = ft_strchr(new, '$');
	new_join(x, var);
	new_join(x, "\"");
	free(new);
}
