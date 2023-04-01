/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:12:16 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/01 14:03:41 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	begin_and_end_with_quote(char *cmd, t_x *x)
{
	new_join(x, "\1'");
	new_join(x, cmd);
	new_join(x, "'");
}

void	begin_with_quote(t_x *x, char *var)
{
	char	*cmd;

	cmd = getenv(var);
	if (cmd == NULL)
		free(cmd);
	else
	{
		new_join(x, "\1'");
		new_join(x, cmd);
		new_join(x, " ");
	}
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
