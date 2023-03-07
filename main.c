/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/04 11:46:02 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/07 23:12:33 by naal-jen         ###   ########.fr       */
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

char	**handle_redirect(char **input, t_flags f)
{
	// char	**new;
	int		fd;

	if (f.append_out == false && f.write_in == false
		&& f.re_in == false && f.re_out == false)
		return (input);
	if (f.re_in == true)
	{
		fd = open(input[1], O_RDONLY);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	else if (f.write_in == true)
	{
		take_input(input[1], &fd);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}

	return (0);
}

void	analize_command(char *line, char **env, t_flags flags)
{
	char	**inputs;
	int		pid;

	if (flags.pipe == true)
	{
		inputs = ft_split(line, '|');
	//	use_pipex(inputs, env);
	}
	else
	{
		pid = fork();
		if (pid == 0)
		{
			inputs = ft_split(line, ' ');
			inputs = handle_redirect(inputs, flags);
			execute(inputs, env);
		}
		waitpid(pid, NULL, 0);
	}
}

// ----------- per il ctrl+c ----------
void	sigint_handler()
{
	printf("\n");
	printf("minishell~$ ");
}

int	main(int argc, char **argv, char **env)
{
	char	*cmd;
	t_flags	flags;

	(void) argc;
	(void) argv;

	//------------ ctrl+c -----------
	signal(SIGINT, sigint_handler);
	//------------ ctrl+\ -----------
	signal(SIGQUIT, SIG_IGN);

	using_history();
	while (1)
	{
		cmd = readline("minishell~$ ");

		//---------- ctrl+d -----------
		//------ ritorna un EOF ------- 
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
			analize_command(cmd, env, flags);
			add_history(cmd);
			free(cmd);
		}
	}
	return (0);
}