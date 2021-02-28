/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:22:59 by joopark           #+#    #+#             */
/*   Updated: 2021/02/28 14:00:12 by joopark          ###   ########.fr       */
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
	char		*exec;
	char		*tmp;
	int			ioerr[3];
	pid_t		a;
	pid_t		b;
	int			stat_loc;

	printf("[%s] I : %d / O : %d\n", __func__, io[0], io[1]);
	cmd = ft_parse_replace_inquote(cmd, ' ', (char)0xff);
	cmd = ft_ext_iofd(cmd, &ioerr[0], &ioerr[1], &ioerr[2]);
	cmd = ft_parse_replace_quote(cmd, ' ');
	arg = ft_parse_split(cmd, ' ', (char)0xff, ' ');
	b = -1;
	stat_loc = -1;
	if (ioerr[0] < 0 || ioerr[1] < 0)
		write(1, "error\n", 6);
	if (arg != NULL && arg[0] != NULL)
	{
		if (ft_check_builtins(arg[0]) == 1)
			ft_exec_builtins(arg, &envp);
		else if (ft_strrchr(arg[0], '/') == NULL)
		{
			exec = ft_find_exec(envp, arg[0]);
			a = ft_exec(exec, arg, envp, io);
			//b = waitpid(a, &stat_loc, 0);
			printf("pid1 : %d, pid2 : %d, stat_loc : %d\n", a, b, stat_loc);
		}
		else
		{
			tmp = getcwd(NULL, 0);
			exec = ft_strnstack(tmp, "/", 1);
			exec = ft_strnstack(exec, arg[0], ft_strlen(arg[0]));
			a = ft_exec(exec, arg, envp, io);
			//b = waitpid(a, &stat_loc, 0);
			printf("pid1 : %d, pid2 : %d, stat_loc : %d\n", a, b, stat_loc);
		}
	}
	if (ioerr[0] > 0)
		close(ioerr[0]);
	if (ioerr[1] > 0)
		close(ioerr[1]);
	ft_strsfree(arg);
}
