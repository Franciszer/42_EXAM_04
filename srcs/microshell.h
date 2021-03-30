/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:57:22 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/30 14:38:57 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// malloc, free, write, close, fork, waitpid, signal, kill, exit, chdir, execve, dup, dup2, pipe, strcmp, strncmp

#ifndef MICROSHELL_H

# define MICROSHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <string.h>
# include <stdio.h>
# include <stdbool.h>

# define PIPE 		"|"
# define SEP 		";"
# define NOT_SET	-1
# define SET(x)		x != NOT_SET
# define INIT_PIPE(pid) if ((pid = fork()) != -1); FATAL_SYSCALL;

# define ERR_RET 			1
# define ERR_CD_BAD_ARGS	"error: cd: bad arguments"
# define FATAL_CD_BAD_ARGS	handle_error_fatal(ERR_CD_BAD_ARGS, ERR_RET)
# define FATAL_CD_CHDIR		handle_error("error: cd: cannot change directory to ");\
								handle_error_fatal(current->data[current->begin + 1], ERR_RET)
# define FATAL_SYSCALL		handle_error_fatal("error: fatal", 1)

# define CHILD(pid)			pid == 0
# define PARENT(pid)		pid != 0

typedef struct	s_command_handler {
	const char	**data;
	const char	**env;
	int			begin;
	int			next_pipe;
	int			next_sep;
	int			end_args;
}				t_command_handler;

# define INIT_COMMAND_HANDLER(name, args, env_vars) \
	name.data = args;\
	name.begin = NOT_SET;\
	name.next_pipe = NOT_SET;\
	name.next_sep = NOT_SET;\
	name.env = (const char**)env_vars;\
	name.end_args = NOT_SET

void	microshell(const char **args, const char **env_vars);

void	ft_putchar_fd(const char c, int fd);

void	ft_pustr_fd(const char *str, int fd);

size_t	ft_strlen(const char *str);

void	handle_error(const char *str);

void	handle_error_fatal(const char *str, const char exit_status);

bool	find_next(t_command_handler *current);

void	exec_command(const t_command_handler *current);

void	exec_pipe(const t_command_handler *current);

void	exec_pipeless(char * const *args, char * const *env, size_t size);

void	bt_cd(const t_command_handler *current);

void	free_args(char **args, const int max_idx);

void	fatal_free_args(char **args, const int max_idx);

char	**copy_args(const t_command_handler *current);

#endif
