/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:57:22 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/29 16:06:16 by frthierr         ###   ########.fr       */
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

typedef struct	s_command_handler {
	const char	**data;
	const char	**env;
	int			begin;
	int			next_pipe;
	int			next_sep;
}				t_command_handler;

# define INIT_COMMAND_HANDLER(name, args, env_vars) \
	name.data = args;\
	name.begin = NOT_SET;\
	name.next_pipe = NOT_SET;\
	name.next_sep = NOT_SET;\
	name.env = (const char**)env_vars;

void	microshell(const char **args, const char **env_vars);

void	ft_putchar_fd(const char c, int fd);

void	ft_pustr_fd(const char *str, int fd);

size_t	ft_strlen(const char *str);

void	handle_error(const char *str);

void	handle_error_fatal(const char *str, const char exit_status);

bool	find_next(t_command_handler *current);

void	exec_current(t_command_handler *current);

#endif
