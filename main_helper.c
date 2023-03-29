/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_helper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/29 13:49:04 by naal-jen          #+#    #+#             */
/*   Updated: 2023/03/29 13:50:33 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	main_helper(t_x *x, char **env, t_flags flags)
{
	char	*cmd;

	cmd = readline("minishell~$ ");
	cmd = exit_status(cmd);
	cmd = control_ex(x, cmd);
	if (cmd == NULL)
	{
		printf("\n");
		free(cmd);
		exit(EXIT_SUCCESS);
	}
	else if (*cmd != '\0')
	{
		flag_init(&flags);
		flag_finder(cmd, &flags);
		analize_command(cmd, &env, flags);
		add_history(cmd);
		free(cmd);
	}
}
