/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_helper.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/24 10:12:16 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/27 08:56:23 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*begin_and_end_with_quote(char *new_str, char *cmd)
{
	new_str = ft_strjoin(new_str, "\1'");
	new_str = ft_strjoin(new_str, cmd);
	new_str = ft_strjoin(new_str, "'");
	return (new_str);
}

char	*begin_with_quote(char *new_str, char *var)
{
	char	*cmd;

	cmd = getenv(var);
	if (cmd == NULL)
	{
		printf("begin_with_quote");
		new_str = NULL;
	}
	else
	{
		new_str = ft_strjoin(new_str, "\1'");
		new_str = ft_strjoin(new_str, cmd);
		new_str = ft_strjoin(new_str, " ");
	}
	return (new_str);
}

char	*end_with_quote(char *new_str, char *str)
{
	char	*var;
	char	*cmd;

	str = ft_strtrim(str, "\'\"");
	var = ft_strchr(str, '$');
	var++;
	cmd = getenv(var);
	if (cmd == NULL)
	{
		printf("end_with_quote");
		new_str = NULL;
	}
	else
	{
		new_str = ft_strjoin(new_str, cmd);
		new_str = ft_strjoin(new_str, "'");
	}
	return (new_str);
}

char	*end_with_dquote(char *new_str, char *str)
{
	char	*var;

	str = ft_strtrim(str, "\'\"");
	var = ft_strchr(str, '$');
	new_str = ft_strjoin(new_str, var);
	new_str = ft_strjoin(new_str, "\"");
	return (new_str);
}
