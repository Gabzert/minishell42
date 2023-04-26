/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:42:19 by gfantech          #+#    #+#             */
/*   Updated: 2023/04/26 12:18:54 by naal-jen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <stdio.h>
# include <readline/readline.h> 
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

# define IN 1
# define OUT 0

typedef struct s_sig
{
	int		g_exit;
	bool	cmd_run;
}	t_sig;

extern t_sig	g_sig;

typedef struct s_pipex
{
	int	**fd;
	int	fd_count;
	int	pid1;
	int	pid2;
	int	pidn;
	int	i;
}	t_pipex;

typedef struct s_flags
{
	bool	re_in;
	bool	re_out;
	bool	write_in;
	bool	append_out;
	bool	pipe;
	bool	quote;
	bool	d_quote;
	int		stdin;
	int		stdout;
}	t_flags;

typedef struct s_size
{
	int		i;
	int		j;
	int		size_cmd;
	int		size_full;
	char	*var;
}	t_size;

typedef struct s_x
{
	int		i;
	int		j;
	int		y;
	int		case_q;
	int		case_dq;
	char	*var;
	char	*new_str;
	char	**str_split;
	char	**envp;
}	t_x;

char	*find_path(char **env);
char	*find_cmd(char *cmd, char **env);
void	take_input(char *eof, int *file);
int		split_size(char **split);
void	flag_finder(char *input, t_flags *flags);
void	flag_init(t_flags *f);
char	**split_cmd(char *line, t_flags fl);

/*
**	FREE UTILS
*/
void	free_child(char **input, t_pipex *pipe);
void	free_pipes(int **fd, int i);
void	close_pipes(int **fd, int i);
void	free_split(char **a);

/*
**	REDIRECT UTILS
*/
char	**handle_redirect(char **input, t_flags f);
void	change_inout(char **input, int *diff, int i_o);
char	**extract_command(char **inputs, int diff);
int		locate_cmd(char **inputs);

void	pipex(int size, char **inputs, char ***env, t_flags flag);
void	pipex_init(t_pipex *p, int size);

/*
**	BUILTINS
*/
int		is_builtin_helper(char *str, int n);
bool	is_builtin(char **inputs, t_x *x, t_flags flag);
void	echo(char **inputs);
void	l_env(char **env);
void	export(char **inputs, t_x **x);
void	unset(char **inputs, t_x **x);
void	reset_io(int fdin, int fdout);
bool	is_any(char **inputs);

/* --------------------------- cmd_utils_helper.c --------------------------- */
void	is_builtin_helper_1(char **inputs);
void	pwd_helper(void);
int		full_size_helper(char *str, int i, int j);
void	not_v_helper(char *str, t_x *x);
void	add_q_s(t_x *x);
void	envcpy(char **env, t_x **x);

/* --------------------------------- main.c --------------------------------- */
void	analize_command(char *line, char ***env, t_flags flags, t_x *x);

/* ------------------------------ main_helper.c ----------------------------- */
void	free_x_1(t_x **x);
void	free_x(t_x **x);
void	main_helper_1(t_x **x);
void	main_helper(t_x *x, char ***env, t_flags flags);

/* ------------------------------ exit_status.c ----------------------------- */
char	*exit_status(char *str);

/* ------------------------------ variable_ex.c ----------------------------- */
void	new_join(t_x *x, char *str);
void	init(t_x *x);
int		full_size(char *str);
void	add_command(char *str, t_x *x);
char	*control_ex(t_x *x, char *str);

/* ----------------------------- variable_ex_1.c ---------------------------- */
void	sis_case_dq(int n, t_x *x);
void	sis_case_q(int n, t_x *x);
void	simple_variable(char *str, t_x *x);
void	helper_ex(char *str, t_x *x);
void	helper_no_echo(t_x *x);

/* ----------------------- one_function_f_norminette.c ---------------------- */
void	add_command_space_helper(char *str, t_x *x);

#endif
