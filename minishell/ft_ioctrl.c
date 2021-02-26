/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:34:53 by joopark           #+#    #+#             */
/*   Updated: 2021/02/26 19:06:56 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파일명으로부터 파일 디스크립터를 얻는 함수 (에러시 에러넘버 음수로 반환)
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
		rtn *= errno;
	return (rtn);
}

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
