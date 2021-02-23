/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:32 by joopark           #+#    #+#             */
/*   Updated: 2021/02/23 20:52:47 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>
#include <string.h>

int				main(int argc, char *argv[], char *envp[])
{
	(void) argc;
	(void) argv;
	char		*bp;
	char		*line;
	char		*exec;
	char		**arg;
	pid_t		a;
	pid_t		b;
	int			stat_loc;
	char		*tmp;

	//chdir("/Users/joohongpark/Documents/code/42/42cursus/minishell/../libft");
	//printf("path : %s\n", tmp);
	ft_signal();
	while (1)
	{
		ft_putstr_fd("\n$> ", 1);
		line = ft_getline(&bp);
		//write(1, line, ft_strlen(line));
		arg = ft_parse_exec(line);
		
		if (arg[0] != NULL)
		{
			if (ft_strrchr(arg[0], '/') == NULL)
				exec = ft_find_exec(envp, arg[0]);
			else
			{
				tmp = getcwd(NULL, 0);
				exec = ft_strnstack(tmp, "/", 1);
				exec = ft_strnstack(exec, arg[0], ft_strlen(arg[0]));
				printf("path : %s\n", exec);
			}
			a = ft_exec(exec, arg, envp);
			b = waitpid(a, &stat_loc, 0);
			printf("pid1 : %d, pid2 : %d, stat_loc : %d\n", a, b, stat_loc);
		}
		free(line);
	}
	return (0);
}
