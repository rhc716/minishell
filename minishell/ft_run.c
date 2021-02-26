/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:22:59 by joopark           #+#    #+#             */
/*   Updated: 2021/02/26 18:29:48 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// 입력된 라인에 대한 명령어를 ; 단위로 나누고 실행
void			ft_run(char *cmd, char *envp[])
{
	char		*line;
	char		**cmds;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, ';', (char)0xff);
	cmds = ft_parse_split(cmd, ';', (char)0xff, ';');
	while (cmds[i] != NULL)
	{

		line = ft_strnstack(ft_strdup(" "), cmds[i], ft_strlen(cmds[i]));
		printf("[%s] %s\n", __func__, line);
		ft_run_with_pipe(line, envp);
		free(line);
		i++;
	}
	ft_strsfree(cmds);
}

// 세미콜론으로 분리된 명령어를 파이프로 나누어진대로 실행
void			ft_run_with_pipe(char *cmd, char *envp[])
{
	char		**cmds;
	char		*line;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, '|', (char)0xff);
	cmds = ft_parse_split(cmd, '|', (char)0xff, '|');
	while (cmds[i] != NULL)
	{
		line = ft_strnstack(ft_strdup(" "), cmds[i], ft_strlen(cmds[i]));
		printf("[%s] %s\n", __func__, line);
		ft_run_cmd(line, envp, 0, 0);
		free(line);
		i++;
	}
	ft_strsfree(cmds);
}

// 가장 작은 명령어 하나에 대해서 실행
void			ft_run_cmd(char *cmd, char *envp[], int i, int o)
{
	char		**arg;
	int			ioerr[3];
	int			j;

	(void) envp;
	(void) i;
	(void) o;
	j = 0;
	cmd = ft_parse_replace_inquote(cmd, ' ', (char)0xff);
	cmd = ft_ext_iofd(cmd, &ioerr[0], &ioerr[1], &ioerr[2]);
	cmd = ft_parse_replace_quote(cmd, ' ');
	arg = ft_parse_split(cmd, ' ', (char)0xff, ' ');
	if (ioerr[0] < 0 || ioerr[1] < 0)
		write(1, "error\n", 6);
	while (arg[j] != NULL)
	{
		printf("[%s] %s\n", __func__, arg[j]);
		j++;
	}
	if (ioerr[0] > 0)
		close(ioerr[0]);
	if (ioerr[1] > 0)
		close(ioerr[1]);
	ft_strsfree(arg);
}
