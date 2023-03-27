/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_helper_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:47:34 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/26 23:50:18 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init(t_x *x)
{
	x->i = 0;
	x->j = 0;
	x->y = 0;
	x->bk = 0;
	x->case_1 = 0;
	x->case_2 = 0;
	x->case_3 = 0;
	x->case_4 = 0;
	x->case_5 = 0;
	x->case_qdq = 0;
	x->start = 0;
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
			size.j = size.i + 1;
			while (str[size.j] && (!(str[size.j] >= 9 && str[size.j] <= 13)))
				size.j++;
			size.var = ft_substr(str, size.i + 1, size.j - size.i);
			size.size_full -= ft_strlen(size.var) + 1;
			size.cmd = getenv(size.var);
			if (size.cmd)
				size.size_cmd += ft_strlen(size.cmd);
			else
				size.size_full += ft_strlen(size.var) + 1;
			size.i = size.j - 1;
		}
		size.i++;
	}
	size.size_cmd += size.size_full;
	return (size.size_cmd + 2);
}

char	*simple_v(char *var, char *new_str)
{
	char	*cmd;

	if (ft_strnstr(var, "$", ft_strlen(var)))
		new_str = split_dollar(new_str, var);
	else
	{
		cmd = getenv(var);
		if (cmd == NULL)
		{
			printf("simple_v\n");
			free(cmd);
			free(new_str);
		}
		else
		{
			new_str = ft_strjoin(new_str, cmd);
			new_str = ft_strjoin(new_str, " ");
		}
	}
	return (new_str);
}

char	*not_v(char *new_str, char *str)
{
	new_str = ft_strjoin(new_str, str);
	new_str = ft_strjoin(new_str, " ");
	return (new_str);
}

char	*split_dollar(char *new_str, char *str)
{
	char	**new_split;
	char	*var;
	char	*cmd;
	int		i;

	i = 0;
	new_split = ft_split(str, '$');
	while (new_split[i])
	{
		var = new_split[i];
		cmd = getenv(var);
		if (cmd == NULL)
		{
			printf("split_dollar\n");
			free(cmd);
			free(var);
		}
		else
			new_str = ft_strjoin(new_str, cmd);
		i++;
	}
	return (new_str);
}
