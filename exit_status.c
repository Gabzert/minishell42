/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 12:24:05 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/29 13:38:53 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*exit_status(char *str)
{
	if (ft_strnstr(str, "$?", 2) && ft_strlen(str) == 2)
		printf("%d: command not found\n", g_exit);
	else if (ft_strnstr(str, "echo $?", 7))
		printf("%d", g_exit);
	g_exit = 0;
	return (str);
}
