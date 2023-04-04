/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable_ex_helper_1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/26 23:47:34 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/04 12:38:03 by naal-jen         ###   ########.fr       */
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
	x->case_q = 0;
	x->start = 0;
	x->var = NULL;
	x->cmd = NULL;
	x->str_split = NULL;
	x->new_str = NULL;
	x->new_split = NULL;
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

void	simple_v(char *var, t_x *x)
{
	char	*new;

	if (ft_strnstr(var, "$", ft_strlen(var)))
	{
		new = ft_strtrim(var, "\"$");
		if (ft_strnstr(new, "$", ft_strlen(new)))
			split_dollar(new, x);
		else
		{
			if (getenv(new))
			{
				new_join(x, getenv(new));
				new_join(x, " ");
			}
		}
		free(new);
	}
	else
	{
		if (getenv(var))
		{
			new_join(x, getenv(var));
			new_join(x, " ");
		}
	}
}

void	not_v(char *str, t_x *x)
{
	char	*new;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			j++;
		i++;
	}
	if (j == 4)
	{
		new = ft_strtrim(str, "'");
		simple_v(new, x);
		free(new);
		return ;
	}
	if (str[0] == '~' && ft_strlen(str) == 1)
		new_join(x, "~");
	else
		not_v_helper(str, x);
}

void	split_dollar(char *str, t_x *x)
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
			new_join(x, cmd);
		i++;
	}
	free_split(new_split);
}
