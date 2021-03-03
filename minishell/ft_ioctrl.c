/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:34:53 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 02:32:00 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파일명으로부터 파일 디스크립터를 얻는 함수 (에러시 표준에러 출력에 에러 출력 및 에러번호 리턴)
int				ft_getfd(char *filename, char mode)
{
	int			rtn;

	if (mode == 'r')
		rtn = open(filename, O_RDONLY);
	else if (mode == 'w')
		rtn = open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG);
	else if (mode == '+')
		rtn = open(filename, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG);
	else
		rtn = 0;
	if (rtn == -1)
	{
		rtn *= errno;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (rtn);
}

// 리다이렉트 기호를 파싱해서 입/출력 파일을 연 후 인수에 저장한다. 에러시 err에 저장.
char			*ft_ext_iofd(char *cmd, int *i, int *o, int *err)
{
	char		*in;
	char		*out;
	char		rp;

	cmd = ft_parse_redirect(cmd, &in, &out, &rp);
	*i = 0;
	*o = 0;
	if (in != NULL)
		*i = ft_getfd(in, 'r');
	if (out != NULL && rp == 'w')
		*o = ft_getfd(out, 'w');
	if (out != NULL && rp == '+')
		*o = ft_getfd(out, '+');
	if (*i < 0)
		*err = *i;
	else if (*o < 0)
		*err = *o;
	else
		*err = 0;
	if (in != NULL)
		free(in);
	if (out != NULL)
		free(out);
	return (cmd);
}

// 파이프 배열을 만든다. (배열끼리 파이프로 이어붙임)
int				**ft_genpipes(int len)
{
	int			**rtn;
	int			i;

	i = 0;
	rtn = malloc(sizeof(int *) * len);
	if (rtn == NULL)
		return (NULL);
	while (i < len)
	{
		rtn[i] = malloc(sizeof(int) * 2);
		if (rtn[i] == NULL)
			return (NULL);
		if (i == 0)
			rtn[i][0] = STDIN_FILENO;
		if ((i + 1) == len)
			rtn[i][1] = STDOUT_FILENO;
		if (i > 0)
		{
			if (ft_genpipe(&rtn[i - 1][1], &rtn[i][0]) == -1)
				return (NULL);
		}
		i++;
	}
	return (rtn);
}

// 파이프 하나를 만든다. (pipe 시스템콜이 배열 입력을 강제하여 만듬)
int				ft_genpipe(int *i, int *o)
{
	int			io[2];
	int			rtn;

	rtn = pipe(io);
	*i = io[1];
	*o = io[0];
	return (rtn);
}

// 파이프를 닫는다.
void			ft_closepipe(int **pipe, int len)
{
	while (--len >= 0)
	{
		if (pipe[len][0] != STDIN_FILENO)
			close(pipe[len][0]);
		if (pipe[len][1] != STDOUT_FILENO)
			close(pipe[len][1]);
		free(pipe[len]);
	}
	free(pipe);
}