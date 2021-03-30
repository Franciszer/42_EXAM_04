/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frthierr <frthierr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/30 14:50:24 by frthierr          #+#    #+#             */
/*   Updated: 2021/03/30 15:10:37 by frthierr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "microshell.h"

int	main(int argc, const char **argv, const char **env) {
	if (argc <= 1) return 1;
	microshell(argv, env);
}
