/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:22:59 by joopark           #+#    #+#             */
/*   Updated: 2021/03/03 01:05:39 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"
//#include <stdio.h>

// 입력된 라인에 대한 명령어를 ; 단위로 나누고 실행
void			ft_run(char *cmd, char **envp[], t_com *com)
{
	char		**cmds;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, ';', (char)0xff);
	cmds = ft_parse_split(cmd, ';', (char)0xff, ';');
	while (cmds[i] != NULL)
	{
		//printf("[%s] %s\n", __func__, cmds[i]);
		ft_run_with_pipe(cmds[i], envp, com);
		i++;
	}
	ft_strsfree(cmds);
}

// 세미콜론으로 분리된 명령어를 파이프로 나누어진대로 실행
void			ft_run_with_pipe(char *cmd, char **envp[], t_com *com)
{
	pid_t		*pids;
	char		**cmds;
	int			**pipes;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, '|', (char)0xff);
	cmds = ft_parse_split(cmd, '|', (char)0xff, '|');
	while (cmds[i] != NULL)
		i++;
	pids = malloc(sizeof(pid_t) * i);
	pipes = ft_genpipes(i);
	i = 0;
	while (cmds[i] != NULL)
	{
		//printf("cmd %d : %s\n", i, cmds[i]);
		pids[i] = ft_run_cmd(cmds[i], envp, pipes[i], com);
		i++;
	}
	com->status = ft_exec_wait(pids, i);
	ft_closepipe(pipes, i);
	ft_strsfree(cmds);
}

// 가장 작은 명령어 하나에 대해서 실행
pid_t			ft_run_cmd(char *cmd, char **envp[], int io[], t_com *com)
{
	pid_t		rtn;
	char		*tmp;
	char		**arg;
	int			ioerr[3];

	tmp = ft_strdup(cmd);
	tmp = ft_parse_replace_inquote(tmp, ' ', (char)0xff);
	tmp = ft_ext_iofd(tmp, &ioerr[0], &ioerr[1], &ioerr[2]);
	tmp = ft_quote_remove(tmp);
	arg = ft_parse_split(tmp, ' ', (char)0xff, ' ');
	//printf("[%s] I : %d / O : %d / cmd : %s\n", __func__, io[0], io[1], tmp);
	free(tmp);
	if (ioerr[0] < 0 || ioerr[1] < 0)
		write(1, "error\n", 6);
	if (ioerr[0] > 0)
		io[0] = ioerr[0];
	if (ioerr[1] > 0)
		io[1] = ioerr[1];
	rtn = ft_run_exec(arg, envp, io, com);
	if (ioerr[0] > 0)
		close(ioerr[0]);
	if (ioerr[1] > 0)
		close(ioerr[1]);
	ft_strsfree(arg);
	return (rtn);
}

// 가장 작은 바이너리 하나에 대해서 실행
pid_t			ft_run_exec(char *args[], char **envp[], int io[], t_com *com)
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
			ft_exec_builtins(args, envp, io, com);
		else if (ft_strrchr(args[0], '/') == NULL)
		{
			exec = ft_find_exec(*envp, args[0]);
			rtn = ft_exec(exec, args, *envp, io);
			//printf("pid : %d\n", rtn);
		}
		else
		{
			tmp = getcwd(NULL, 0);
			exec = ft_strnstack(tmp, "/", 1);
			exec = ft_strnstack(exec, args[0], ft_strlen(args[0]));
			rtn = ft_exec(exec, args, *envp, io);
			//printf("pid : %d\n", rtn);
		}
	}
	return (rtn);
}
