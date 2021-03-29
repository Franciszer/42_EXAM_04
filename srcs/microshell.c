/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:56:29 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/29 16:06:49 by frthierr         ###   ########.fr       */
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

bool	find_next(t_command_handler *current) {
	int		i = current->begin;
	bool	valid = false;
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
	printf("MIDDLE\n");
	while (current->data[++i]) {
		if (!strcmp(PIPE, current->data[i])) {
				current->next_pipe = i;
				return true;
			}
		if (!strcmp(SEP, current->data[i])) {
			current->next_sep = i;
			return true;
		}
			
	}
	return true;
}



void	microshell(const char **args, const char **env_vars) {
	t_command_handler	command_handler;
	
	INIT_COMMAND_HANDLER(command_handler, args, env_vars);
	find_next(&command_handler);
}