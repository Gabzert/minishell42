/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 16:20:45 by gfantech          #+#    #+#             */
/*   Updated: 2023/04/26 14:11:45 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_builtin(t_pipex pipe, char *line, t_x *x, t_flags flag)
{
	char	**inputs;

	inputs = split_cmd(line, flag);
	if (is_any(inputs) == true)
	{
		if (pipe.i == 0)
		{
			if (!ft_strchr(line, '>'))
				dup2(pipe.fd[pipe.i][1], 1);
		}
		else if (pipe.i == pipe.fd_count)
		{
			if (!ft_strchr(line, '<'))
				dup2(pipe.fd[pipe.i][0], 0);
		}
		else
		{
			if (!ft_strchr(line, '<'))
				dup2(pipe.fd[pipe.i][0], 0);
			if (!ft_strchr(line, '>'))
				dup2(pipe.fd[pipe.i + 1][1], 1);
		}
		is_builtin(inputs, x, flag);
		free_child(inputs, &pipe);
	}
}

static void	run_child_first(t_pipex pipe, char *line, t_x *x, t_flags flag)
{
	char	**input;
	char	*cmd;

	check_builtin(pipe, line, x, flag);
	input = split_cmd(line, flag);
	input = handle_redirect(input, flag);
	if (access(input[0], X_OK) != 0)
		cmd = find_cmd(input[0], x->envp);
	else
		cmd = input[0];
	if (cmd == NULL)
		free_child(input, &pipe);
	if (!ft_strchr(line, '>'))
		dup2(pipe.fd[pipe.i][1], 1);
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

	check_builtin(pipe, line, x, flag);
	input = split_cmd(line, flag);
	input = handle_redirect(input, flag);
	if (access(input[0], X_OK) != 0)
		cmd = find_cmd(input[0], x->envp);
	else
		cmd = input[0];
	if (cmd == NULL)
		free_child(input, &pipe);
	if (!ft_strchr(line, '<'))
		dup2(pipe.fd[pipe.i][0], 0);
	if (!ft_strchr(line, '>'))
		dup2(pipe.fd[pipe.i + 1][1], 1);
	close_pipes(pipe.fd, pipe.fd_count - 1);
	if (execve(cmd, input, x->envp) == -1)
		free_child(input, &pipe);
}

static void	run_child_last(t_pipex pipe, char *line, t_x *x, t_flags flag)
{
	char	**input;
	char	*cmd;

	check_builtin(pipe, line, x, flag);
	input = split_cmd(line, flag);
	input = handle_redirect(input, flag);
	if (access(input[0], X_OK) != 0)
		cmd = find_cmd(input[0], x->envp);
	else
		cmd = input[0];
	if (cmd == NULL)
		free_child(input, &pipe);
	if (!ft_strchr(line, '<'))
		dup2(pipe.fd[pipe.i][0], 0);
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
