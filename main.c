/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/07 11:22:21 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **input, char **env)
{
	char	*cmd;
	int		pid;
//	int		file;

	pid = fork();
	if (pid == 0)
	{
		cmd = find_cmd(input[0], env);
		if (execve(cmd, input, env) == -1)
			return ;
	}
	waitpid(pid, NULL, 0);
}

void	analize_command(char *line, char **env, t_flags flags)
{
	char	**inputs;


	if (flags.pipe == true)
	{
		inputs = ft_split(line, '|');
	//	use_pipex(inputs, env);
	}
	else
	{
		inputs = ft_split(line, ' ');
		execute(inputs, env);
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
			flag_finder(cmd, &flags);
			analize_command(cmd, env, flags);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}