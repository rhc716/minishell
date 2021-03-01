/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:32 by joopark           #+#    #+#             */
/*   Updated: 2021/03/01 14:48:13 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

int				main(int argc, char *argv[], char *envp[])
{
	char		**env;
	char		*bp;
	char		*line;

	(void) argc;
	(void) argv;

	ft_signal();
	env = ft_strsdup(envp);
	bp = NULL;
	ft_loginmsg("./prompt");
	while (1)
	{
		ft_putstr_fd("\n$> ", 1);
		line = ft_getline(&bp);
		ft_run(line, env);
		free(line);
	}
	return (0);
}