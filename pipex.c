/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:20:45 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/06 17:34:20 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_child_first(t_pipex pipe, char *line, char **env, t_flags flag)
{
	char	**input
	char	*cmd;

	input = ft_split(line, ' ');
	if (flag.re_in == true || flag.write_in == true)
	{
		change_input(input, flag);
		input = extract_command(input, flag);
	}
	cmd = find_cmd(input[0], env);
	if (cmd == NULL)
		free_child(input, &pipe);
	dup2(pipe.fd[pipe.i][1], 1);
	close_pipes(pipe.fd, pipe.fd_count - 1);
	if (execve(cmd, input, env) == -1)
	{
		perror("execution failed");
		free_child(input, &pipe);
	}
}

void	run_child_middle(t_pipex pipe, char **input, char **env)
{
	char	*cmd;

	cmd = find_cmd(input[0], env);
	if (cmd == NULL)
		free_child(input, &pipe);
	dup2(pipe.fd[pipe.i][0], 0);
	dup2(pipe.fd[pipe.i + 1][1], 1);
	close_pipes(pipe.fd, pipe.fd_count - 1);
	if (execve(cmd, input, env) == -1)
		free_child(input, &pipe);
}

void	run_child_last(t_pipex pipe, char *line, char **env, t_flags flag)
{
	char	**input
	char	*cmd;

	input = ft_split(line, ' ');
	if (flag.re_in == true || flag.write_in == true)
	{
		change_output(input, flag);
		input = extract_command(input, flag);
	}
	cmd = find_cmd(input[0], env);
	if (cmd == NULL)
		free_child(input, &pipe);
	dup2(pipe.fd[pipe.i][0], 0);
	close_pipes(pipe.fd, pipe.fd_count - 1);
	if (execve(cmd, input, env) == -1)
		free_child(input, &pipe);
}

void	pipex(int size, char **inputs, char **env, t_flags flag)
{
	t_pipex	pipe;

	pipex_init(&pipe, inputs, size);
	pipe.pid1 = fork();
	if (pipe.pid1 == 0)
		run_child_first(pipe, inputs[0], env, flag);
	waitpid(pipe.pid1, NULL, 0);
	if (flag.write_in == true)
		unlink(".here_doc");
	if (size > 2)
	{
		while (pipe.i < size - 2)
		{
			pipe.pidn = fork();
			if (pipe.pidn == 0)
				run_child_middle(pipe, ft_split(inputs[pipe.i], ' '), env);
			pipe.i++;
		}
	}
	pipe.pid2 = fork();
	if (pipe.pid2 == 0)
		run_child_last(pipe, inputs[size], env, flag);
	free_pipes(pipe.fd, pipe.fd_count - 1);
	waitpid(pipe.pidn, NULL, 0);
	waitpid(pipe.pid2, NULL, 0);
}
