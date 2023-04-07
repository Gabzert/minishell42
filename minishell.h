/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: naal-jen <naal-jen@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 12:42:19 by gfantech          #+#    #+#             */
/*   Updated: 2023/04/07 14:38:17 by naal-jen         ###   ########.fr       */
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
	int		len;
	int		size_for_malloc;
	int		i;
	int		j;
	int		y;
	int		case_1;
	int		case_2;
	int		case_3;
	int		case_4;
	int		case_5;
	int		case_qdq;
	int		case_q;
	int		case_f_q;
	int		start;
	int		bk;
	char	*var;
	char	*cmd;
	char	*new_str;
	char	**str_split;
	char	**new_split;
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
bool	is_builtin(char **inputs, char ***env, t_x *x, t_flags flag);
void	echo(char **inputs);
void	l_env(char **env);
void	export(char **inputs, char ***env, t_x **x);
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
int		simple_v_helper(char *new, t_x *x);
void	helper_4(t_x *x);
void	helper_5(t_x *x);
void	helper_6(t_x *x);
char	*control_ex(t_x *x, char *str);

/* --------------------- variable_ex_helper.c --------------------- */
void	check_for_dq_and_qd_helper_2(t_x *x);
void	begin_and_end_with_quote(char *cmd, t_x *x);
void	begin_with_quote(t_x *x, char *var);
void	end_with_quote(t_x *x, char *str);
void	end_with_dquote(t_x *x, char *str);

/* --------------------- variable_ex_helper_1.c --------------------- */
void	init(t_x *x);
int		full_size(char *str);
void	simple_v(char *var, t_x *x);
void	not_v(char *str, t_x *x);
void	split_dollar(char *str, t_x *x);

/* ------------------------- variable_ex_process_1.c ------------------------ */
void	new_join(t_x *x, char *str);
void	add_command(t_x *x);
void	check_for_dq_and_qd_helper(t_x *x);
void	check_for_dq_and_qd(t_x *x);
void	add_cmd_q_c3(t_x *x);

/* ------------------------- variable_ex_process_2.c ------------------------ */
void	begin_w_q_c3(t_x *x);
void	clean_var(t_x *x);
void	remove_last_q_add_q(t_x *x);
void	case_3_helper(t_x *x);
void	case_1_helper(t_x *x);

/* ------------------------- variable_ex_process_3.c ------------------------ */
void	add_var(t_x *x);
void	add_q_var_c3(t_x *x);
void	remove_lase_dq_add_dq(t_x *x);
void	case_1_helper_0(t_x *x);
void	helper_dq_2(t_x *x);

/* ------------------------- variable_ex_process_4.c ------------------------ */
void	helper_dq_1(t_x *x);
void	helper_dq_d(t_x *x);
void	helper_d(t_x *x);
void	helper_q_c(t_x *x);
void	add_cmd_with_fq_or_with_flq(t_x *x);

/* ------------------------- variable_ex_process_5.c ------------------------ */
void	case_1_and_dollar_and_quote(t_x *x);
void	clear_case_1_and_dollar(t_x *x);
void	dq_with_var(t_x *x);
void	quote(t_x *x);
void	identify_start_dq_q(t_x *x);

/* ------------------------- variable_ex_process_6.c ------------------------ */
void	identify_end_dq_q(t_x *x);
void	identify_start_q_dq(t_x *x);
void	identify_end_q_dq(t_x *x);
void	identify(t_x *x);
void	helper_dq_var(t_x *x);

/* ------------------------- variable_ex_process_7.c ------------------------ */
void	case_31_helper(t_x *x);
void	case_11_helper(t_x *x);
void	helper_1(t_x *x);
void	helper_2(t_x *x);
void	helper_3(t_x *x);

#endif
