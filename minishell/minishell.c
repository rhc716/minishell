/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:32 by joopark           #+#    #+#             */
/*   Updated: 2021/02/28 12:37:18 by joopark          ###   ########.fr       */
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
/*
	char		*exec;
	char		**arg;
	pid_t		a;
	pid_t		b;
	int			stat_loc;
	char		*tmp;
	char		*in;
	char		*out;
	char		rp;
	int			io[2] = {0, 0};
*/

	ft_signal();
	env = ft_strsdup(envp);
	bp = NULL;
	while (1)
	{
		ft_putstr_fd("\n$> ", 1);
		line = ft_getline(&bp);
		ft_run(line, env);
		/*
		line = ft_parse_replace_inquote(line, ' ', (char)0xff);
 		line = ft_parse_replace_quote(line, ' ');
		line = ft_parse_redirect(line, &in, &out, &rp); // 리다이렉트 파서
		printf("in : %s, out : %s, rp : %c\n", in, out, rp);
		if (in != NULL)
			io[0] = ft_getfd(in, 'r');
		if (out != NULL && rp == 'w')
			io[1] = ft_getfd(out, 'w');
		if (out != NULL && rp == '+')
			io[1] = ft_getfd(out, '+');
		printf("in : %d, out : %d\n", io[0], io[1]);
		arg = ft_parse_split(line, ' ', (char)0xff, ' ');
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
				ft_exec_builtins(arg, &env);
			else
			{
				a = ft_exec(exec, arg, env, io);
				b = waitpid(a, &stat_loc, 0);
				if (io[0] > 0)
					close(io[0]);
				if (io[1] > 0)
					close(io[1]);
			}
			printf("pid1 : %d, pid2 : %d, stat_loc : %d\n", a, b, stat_loc);
		}
		if (arg != NULL)
			ft_strsfree(arg);
		*/
		free(line);
	}
	return (0);
}