/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:22:59 by joopark           #+#    #+#             */
/*   Updated: 2021/02/28 16:18:24 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// 입력된 라인에 대한 명령어를 ; 단위로 나누고 실행
void			ft_run(char *cmd, char *envp[])
{
	char		**cmds;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, ';', (char)0xff);
	cmds = ft_parse_split(cmd, ';', (char)0xff, ';');
	while (cmds[i] != NULL)
	{
		printf("[%s] %s\n", __func__, cmds[i]);
		ft_run_with_pipe(cmds[i], envp);
		i++;
	}
	ft_strsfree(cmds);
}

// 세미콜론으로 분리된 명령어를 파이프로 나누어진대로 실행
void			ft_run_with_pipe(char *cmd, char *envp[])
{
	char		**cmds;
	int			**pipes;
	int			pipe[2];
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, '|', (char)0xff);
	cmds = ft_parse_split(cmd, '|', (char)0xff, '|');
	while (cmds[i] != NULL)
		i++;
	pipes = ft_genpipe(i);
	i = 0;
	while (cmds[i] != NULL)
	{
		if (i > 0)
			printf("[%s] pipe %d<-%d\n", __func__, pipes[i - 1][0], pipes[i - 1][1]);
		if (i == 0)
			pipe[0] = STDIN_FILENO;
		else
			pipe[0] = pipes[i - 1][0];
		if (cmds[i + 1] == NULL)
			pipe[1] = STDOUT_FILENO;
		else
			pipe[1] = pipes[i][1];
		printf("[%s] %s\n", __func__, cmds[i]);
		ft_run_cmd(cmds[i], envp, pipe);
		i++;
	}
	ft_closepipe(pipes, i);
	ft_strsfree(cmds);
}

// 가장 작은 명령어 하나에 대해서 실행
void			ft_run_cmd(char *cmd, char *envp[], int io[])
{
	char		**arg;
	int			ioerr[3];
	pid_t		run;

	printf("[%s] I : %d / O : %d\n", __func__, io[0], io[1]);
	cmd = ft_parse_replace_inquote(cmd, ' ', (char)0xff);
	cmd = ft_ext_iofd(cmd, &ioerr[0], &ioerr[1], &ioerr[2]);
	cmd = ft_parse_replace_quote(cmd, ' ');
	arg = ft_parse_split(cmd, ' ', (char)0xff, ' ');
	if (ioerr[0] < 0 || ioerr[1] < 0)
		write(1, "error\n", 6);
	if (ioerr[0] > 0)
		io[0] = ioerr[0];
	if (ioerr[1] > 0)
		io[1] = ioerr[1];
	run = ft_run_exec(arg, envp, io);
	if (ioerr[0] > 0)
		close(ioerr[0]);
	if (ioerr[1] > 0)
		close(ioerr[1]);
	ft_strsfree(arg);
}

// 가장 작은 바이너리 하나에 대해서 실행
pid_t			ft_run_exec(char *args[], char *envp[], int io[])
{
	char		*exec;
	char		*tmp;
	pid_t		rtn;
	pid_t		b;
	int			stat_loc;

	b = -1;
	stat_loc = -1;
	rtn = 0;
	if (args != NULL && args[0] != NULL)
	{
		if (ft_check_builtins(args[0]) == 1)
			ft_exec_builtins(args, &envp);
		else if (ft_strrchr(args[0], '/') == NULL)
		{
			exec = ft_find_exec(envp, args[0]);
			rtn = ft_exec(exec, args, envp, io);
			//b = waitpid(a, &stat_loc, 0);
			printf("pid1 : %d, pid2 : %d, stat_loc : %d\n", rtn, b, stat_loc);
		}
		else
		{
			tmp = getcwd(NULL, 0);
			exec = ft_strnstack(tmp, "/", 1);
			exec = ft_strnstack(exec, args[0], ft_strlen(args[0]));
			rtn = ft_exec(exec, args, envp, io);
			//b = waitpid(a, &stat_loc, 0);
			printf("pid1 : %d, pid2 : %d, stat_loc : %d\n", rtn, b, stat_loc);
		}
	}
	return (rtn);
}
