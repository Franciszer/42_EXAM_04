/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:56:29 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/30 15:09:40 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

void	ft_putchar_fd(const char c, int fd) {
	write(fd, &c, 1);
}

void	ft_pustr_fd(const char *str, int fd) {
	write(fd, str, ft_strlen(str));
}

size_t	ft_strlen(const char *str) {
	size_t	i = 0;
	while (str[i]) i++;
	return i;
}

void	handle_error(const char *str) {
	ft_pustr_fd(str, STDERR_FILENO);
}

void	handle_error_fatal(const char *str, const char exit_status) {
	handle_error(str);
	exit (exit_status);	
}

void	free_args(char **args, const int max_idx) {
	for (int i = 0; i < max_idx ; i++)
		free(args[i]);
	free(args);
	args = NULL;
}

void	fatal_free_args(char **args, const int max_idx) {
	handle_error("error: cannot execute ");
	handle_error(args[0]);
	free_args(args, max_idx);
	exit (1);
}

char	**copy_args(const t_command_handler *current) {
	char **args;
	
	if (!(args = malloc(sizeof(char*) * ((current->end_args - current->begin) + 1))))
		FATAL_SYSCALL;
	for (int i = current->begin; i < current->end_args ; i++) {
		if (!(args[i - current->begin] = malloc\
			(sizeof(char) * (ft_strlen(current->data[i]) + 1))))
				fatal_free_args(args, i);
		else
			strcpy(args[i - current->begin], current->data[i]);
	}
	return args;
}

bool	find_next(t_command_handler *current) {
	int		i;
	if (SET(current->next_pipe))
		i = current->next_pipe;
	else if (SET(current->next_sep))
		i = current->next_sep;
	else
		i = current->begin;
	bool	valid = false;
	current->next_sep = NOT_SET;
	current->next_pipe = NOT_SET;
	while (current->data[++i]) {
		if (strcmp(PIPE, current->data[i]) &&\
			strcmp(SEP, current->data[i])) {
				valid = true;
				current->begin = i;
				break;
			}
	}
	if 		(!valid) return false;
	else if (!current->data[i]) return true;
	while (current->data[++i]) {
		if (!strcmp(PIPE, current->data[i])) {
				current->next_pipe = i;
				current->end_args = current->next_pipe - current->begin;
				return true;
			}
		else if (!strcmp(SEP, current->data[i])) {
			current->next_sep = i;
			current->end_args = current->next_sep - current->begin;
			return true;
		}
	}
	current->end_args = i - current->begin;
	return true;
}

void	bt_cd(const t_command_handler *current) {
	if (current->end_args != 1) {
			FATAL_CD_BAD_ARGS;
		}
	if (chdir(current->data[current->begin + 1]) == -1)
		FATAL_CD_CHDIR;
}

void	exec_pipeless(char * const *args, char * const *env, size_t size) {
	pid_t	pid;

	INIT_PIPE(pid);
	if (CHILD(pid)) {
		if (execve(args[0], args, env) == -1)
			fatal_free_args((char**)args, size);
	}
	else
		waitpid(pid, NULL, 0);
}

void	exec_command(const t_command_handler *current) {
	char **args = copy_args(current);
	size_t	size = current->end_args - current->begin;
	
	exec_pipeless((char *const*)args, (char *const*)current->env, size);
	free_args(args, size);
}

void	microshell(const char **args, const char **env_vars) {
	t_command_handler	command_handler;
	
	
	INIT_COMMAND_HANDLER(command_handler, args, env_vars);
	printf("LESSGO");
	while(find_next(&command_handler)) exec_command(&command_handler);
	return ;
}