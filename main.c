/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/07 17:07:41 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **input, char **env)
{
	char	*cmd;

	cmd = find_cmd(input[0], env);
	if (execve(cmd, input, env) == -1)
		return ;
}

void	analize_command(char *line, char **env, t_flags flags)
{
	char	**inputs;
	int		pid;

	if (flags.pipe == true)
	{
		inputs = ft_split(line, '|');
		pipex(split_size(inputs), inputs, env, flags);
		free_split(inputs);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			inputs = ft_split(line, ' ');
			inputs = handle_redirect(inputs, flags);
			execute(inputs, env);
			free(inputs);
		}
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_flags	flags;

	(void) argc;
	(void) argv;
	using_history();
	while (1)
	{
		cmd = readline("minishell~$ ");
		if (cmd == NULL)
			break ;
		if (*cmd != '\0')
		{
			flag_init(&flags);
			flag_finder(cmd, &flags);
			analize_command(cmd, env, flags);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}