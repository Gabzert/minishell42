/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/06 17:19:07 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute(char **input, char **env)
{
	char	*cmd;
//	int		file;

	cmd = find_cmd(input[0], env);
	if (execve(cmd, input, env) == -1)
		return ;
}

void	analize_command(char *line, char **env)
{
	char	**inputs;
	int		pid;

	if (ft_strchr(line, '|'))
	{
		inputs = ft_split(line, '|');
	//	use_pipex(inputs, env);
	}
	else
	{
		inputs = ft_split(line, ' ');
		pid = fork();
		if (pid == 0)
			execute(inputs, env);
		waitpid(pid, NULL, 0);
	}
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;

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
			analize_command(cmd, env);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}