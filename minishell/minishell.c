/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:32 by joopark           #+#    #+#             */
/*   Updated: 2021/02/25 16:30:04 by joopark          ###   ########.fr       */
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
	char		**env;
	char		*in;
	char		*out;
	char		rp;


	ft_signal();
	env = ft_strsdup(envp);
	bp = NULL;
	while (1)
	{
		ft_putstr_fd("\n$> ", 1);
		line = ft_getline(&bp);
		line = ft_remove_quote(line);
		line = ft_parse_redirect(line, &in, &out, &rp); // 리다이렉트 파서
		printf("in : %s, out : %s, rp : %c\n", in, out, rp);
		arg = ft_parse_exec(line);
		if (arg != NULL && arg[0] != NULL)
		{
			if (ft_strrchr(arg[0], '/') == NULL)
				exec = ft_find_exec(env, arg[0]);
			else
			{
				tmp = getcwd(NULL, 0);
				exec = ft_strnstack(tmp, "/", 1);
				exec = ft_strnstack(exec, arg[0], ft_strlen(arg[0]));
				printf("path : %s\n", exec);
			}
			if (ft_check_builtins(arg[0]) == 1)
				ft_exec_builtins(arg, env);
			else
			{
				a = ft_exec(exec, arg, env);
				b = waitpid(a, &stat_loc, 0);
			}
			printf("pid1 : %d, pid2 : %d, stat_loc : %d\n", a, b, stat_loc);
		}
		if (arg != NULL)
			ft_strsfree(arg);
		free(line);
	}
	return (0);
}
