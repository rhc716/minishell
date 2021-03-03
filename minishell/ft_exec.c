/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:33:02 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 01:37:05 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파일경로, 아규먼트, 환경변수를 받아 프로세스를 실행하여 자식 프로세스의 PID를 리턴 (free 필요없음)
pid_t			ft_exec(char *file, char *argv[], char *envp[], int fd[])
{
	pid_t		rtn;
	int			io[2];

	rtn = fork();
	if (rtn == 0)
	{
		if (fd[0] != STDIN_FILENO)
			io[0] = dup2(fd[0], STDIN_FILENO);
		if (fd[1] != STDOUT_FILENO)
			io[1] = dup2(fd[1], STDOUT_FILENO);
		execve(file, argv, envp);
	}
	else
	{
		if (fd[0] != STDIN_FILENO)
			close(fd[0]);
		if (fd[1] != STDOUT_FILENO)
			close(fd[1]);
	}
	return (rtn);
}

// 인수로 입력된 파일이 실행 가능한지를 판별함 (실행 가능하면 1 리턴)
int				ft_isexecutable(char *file)
{
	struct stat	test;

	if (stat(file, &test) != -1)
		return (1);
	else
		return (0);
}

// env 내의 PATH 중 실행 가능한 명령어 찾기. 실행 가능하면 파일경로 리턴 (free 필요)
char			*ft_find_exec_path(char *envp[], char *cmd)
{
	char		*rtn;
	char		**paths;
	int			j;
	
	j = 0;
	rtn = NULL;
	paths = ft_split(ft_getenv(envp, "PATH"), ':');
	if (paths == NULL)
		return (NULL);
	while (paths[j] != NULL)
	{
		paths[j] = ft_strnstack(paths[j], "/", 1);
		paths[j] = ft_strnstack(paths[j], cmd, ft_strlen(cmd));
		if (ft_isexecutable(paths[j]) == 1 && rtn == NULL)
			rtn = paths[j];
		else
			free(paths[j]);
		j++;
	}
	free(paths[j]);
	free(paths);
	return (rtn);
}

// 실행 가능하면 파일경로 리턴, 불가능하면 NULL 리턴 (free 필요)
char			*ft_find_exec(char *envp[], char *cmd)
{
	char		*rtn;
	char		*tmp;

	if (ft_strrchr(cmd, '/') == NULL)
		rtn = ft_find_exec_path(envp, cmd);
	else
	{
		tmp = getcwd(NULL, 0);
		rtn = ft_strnstack(tmp, "/", 1);
		rtn = ft_strnstack(rtn, cmd, ft_strlen(cmd));
		if (ft_isexecutable(rtn) != 1)
		{
			free(rtn);
			rtn = NULL;
		}
	}
	return (rtn);
}

// pids 배열의 pid들을 기다린다.
int				ft_exec_wait(pid_t *pids, int n)
{
	int			stat_loc;
	int			tmp;
	int			rtn;
	int			i;

	rtn = 0;
	i = 0;
	while (i < n)
	{
		if (pids[i] > 0)
		{
			tmp = waitpid(pids[i], &stat_loc, 0);
			rtn = ((stat_loc >> 8) & 0x000000ff); //rtn = WEXITSTATUS(stat_loc);
		}
		else if (pids[i] < 0)
			rtn = pids[i] * -1;
		i++;
	}
	free(pids);
	return (rtn);
}
