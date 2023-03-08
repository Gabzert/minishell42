/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gfantech <gfantech@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:54:42 by gfantech          #+#    #+#             */
/*   Updated: 2023/03/07 16:56:11 by gfantech         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(char **env)
{
	int		i;
	char	*path;

	i = 0;
	while (ft_strncmp("PATH", env[i], 4) != 0)
		i++;
	path = env[i];
	path += 5;
	return (path);
}

char	*find_cmd(char *cmd, char **env)
{
	char	**path_list;
	char	*command;
	char	*tmp;
	int		i;

	i = 0;
	path_list = ft_split(find_path(env), ':');
	while (path_list[i])
	{
		tmp = ft_strjoin(path_list[i], "/");
		command = ft_strjoin(tmp, cmd);
		if (access(command, X_OK) == 0)
			return (command);
		free(command);
		free(tmp);
		i++;
	}
	while (--i >= 0)
		free(path_list[i]);
	free(path_list);
	write(2, "command not found : ", 20);
	write(2, cmd, ft_strlen(cmd));
	write(2, "\n", 1);
	return (NULL);
}

void	take_input(char *eof, int *file)
{
	char	*str;
	int		len;
	int		fd;

	len = ft_strlen(eof);
	fd = open(".heredoc", O_WRONLY | O_CREAT, 0777);
	while (1)
	{
		write(1, "heredoc>", 9);
		str = get_next_line(0);
		if (ft_strncmp(str, eof, len) == 0)
			break ;
		write(fd, str, ft_strlen(str));
	}
	close(fd);
	*file = open(".heredoc", O_RDONLY);
}