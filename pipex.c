/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:20:45 by gfantech          #+#    #+#             */
/*   Updated: 2023/05/10 15:07:08 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_builtin(t_pipex pipe, char *line, t_x *x, t_flags flag)
{
	char	**inputs;

	inputs = split_cmd(line, flag);
	if (is_any(inputs) == true)
	{
		close_pipes(pipe.fd, pipe.fd_count - 1);
		is_builtin(inputs, x, flag);
		exit(0);
	}
	free_split(inputs);
}

static void	run_child_first(t_pipex pipe, char *line, t_x *x, t_flags flag)
{
	char	**input;
	char	*cmd;

	flag_finder(line, &flag, true);
	if (!ft_strchr(line, '>'))
		dup2(pipe.fd[pipe.i][1], 1);
	check_builtin(pipe, line, x, flag);
	input = split_cmd(line, flag);
	input = handle_redirect(input, flag, true);
	if (access(input[0], X_OK) != 0)
		cmd = find_cmd(input[0], x->envp);
	else
		cmd = input[0];
	if (cmd == NULL)
		free_child(input, &pipe);
	close_pipes(pipe.fd, pipe.fd_count - 1);
	if (execve(cmd, input, x->envp) == -1)
	{
		perror("execution failed");
		free_child(input, &pipe);
	}
}

static void	run_child_middle(t_pipex pipe, char *line, t_x *x, t_flags flag)
{
	char	**input;
	char	*cmd;

	flag_finder(line, &flag, true);
	if (!ft_strchr(line, '<'))
		dup2(pipe.fd[pipe.i][0], 0);
	if (!ft_strchr(line, '>'))
		dup2(pipe.fd[pipe.i + 1][1], 1);
	check_builtin(pipe, line, x, flag);
	input = split_cmd(line, flag);
	input = handle_redirect(input, flag, true);
	if (access(input[0], X_OK) != 0)
		cmd = find_cmd(input[0], x->envp);
	else
		cmd = input[0];
	if (cmd == NULL)
		free_child(input, &pipe);
	close_pipes(pipe.fd, pipe.fd_count - 1);
	if (execve(cmd, input, x->envp) == -1)
		free_child(input, &pipe);
}

static void	run_child_last(t_pipex pipe, char *line, t_x *x, t_flags flag)
{
	char	**input;
	char	*cmd;

	flag_finder(line, &flag, true);
	check_builtin(pipe, line, x, flag);
	if (!ft_strchr(line, '<'))
		dup2(pipe.fd[pipe.i][0], 0);
	input = split_cmd(line, flag);
	input = handle_redirect(input, flag, true);
	if (access(input[0], X_OK) != 0)
		cmd = find_cmd(input[0], x->envp);
	else
		cmd = input[0];
	if (cmd == NULL)
		free_child(input, &pipe);
	close_pipes(pipe.fd, pipe.fd_count - 1);
	if (execve(cmd, input, x->envp) == -1)
		free_child(input, &pipe);
}

void	pipex(int size, char **inputs, t_x *x, t_flags flag)
{
	t_pipex	pipe;

	pipex_init(&pipe, size);
	pipe.pid1 = fork();
	if (pipe.pid1 == 0)
		run_child_first(pipe, inputs[0], x, flag);
	waitpid(pipe.pid1, NULL, WNOHANG);
	if (flag.write_in == true)
		unlink(".heredoc");
	if (size > 2)
	{
		while (pipe.i < size - 2)
		{
			pipe.pidn = fork();
			if (pipe.pidn == 0)
				run_child_middle(pipe, inputs[pipe.i + 1], x, flag);
			pipe.i++;
		}
	}
	pipe.pid2 = fork();
	if (pipe.pid2 == 0)
		run_child_last(pipe, inputs[size - 1], x, flag);
	free_pipes(pipe.fd, pipe.fd_count - 1);
	waitpid(pipe.pidn, NULL, 0);
	waitpid(pipe.pid2, NULL, 0);
}
