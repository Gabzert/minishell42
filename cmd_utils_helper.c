/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/01 13:42:56 by naal-jen          #+#    #+#             */
/*   Updated: 2023/04/01 14:13:30 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	is_builtin_helper_1(char **inputs)
{
	int	n;

	n = 0;
	if (inputs[1] == NULL)
		n = is_builtin_helper("~", n);
	else
		n = is_builtin_helper(inputs[1], n);
	if (n < 0)
		g_exit = 1;
}

void	pwd_helper(void)
{
	char	*buffer;

	buffer = NULL;
	buffer = getcwd(NULL, 0);
	getcwd(buffer, sizeof(buffer));
	ft_printf("%s\n", buffer);
	free(buffer);
}

int	full_size_helper(char *str, int i, int j)
{
	j = i + 1;
	while (str[j] && (!(str[j] >= 9 && str[j] <= 13))
		&& str[j] != '$' && str[j] != '\'' && str[j] != '\"')
		j++;
	return (j);
}

void	not_v_helper(char *str, t_x *x)
{
	char	*new;

	new = ft_strtrim(str, "'");
	new_join(x, new);
	new_join(x, " ");
	free (new);
}

void	add_q_s(t_x *x)
{
	new_join(x, "\1'");
	new_join(x, " ");
}
