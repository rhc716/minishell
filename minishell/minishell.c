/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:32 by joopark           #+#    #+#             */
/*   Updated: 2021/03/03 00:55:42 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
#include <stdio.h>

int				main(int argc, char *argv[], char *envp[])
{
	char		**env;
	char		*bp;
	char		*line;
	t_com		com;

	(void) argc;
	(void) argv;
	com.status = 0;

	ft_signal();
	env = ft_strsdup(envp);
	bp = NULL;
	ft_loginmsg("./prompt");
	while (1)
	{
		ft_prompt();
		line = ft_getline(&bp);
		ft_run(line, &env, &com);
		printf("$? : %d\n", com.status);
		free(line);
	}
	return (0);
}