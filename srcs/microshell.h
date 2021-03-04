/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/04 09:57:22 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/04 10:02:01 by frthierr         ###   ########.fr       */
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

int	ret1(void);

#endif
