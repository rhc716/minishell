/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_console.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:21:07 by joopark           #+#    #+#             */
/*   Updated: 2021/03/02 00:06:06 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 프롬프트를 출력함.
void			ft_prompt(void)
{
	char		*pwd;
	char		**tokens;
	int			i;

	i = 0;
	ft_putstr_fd("\n$ ", 1);
	pwd = getcwd(NULL, 0);
	tokens = ft_split(pwd, '/');
	ft_ansi_escape(5);
	while (tokens[i] != NULL)
		i++;
	if (i == 0)
		ft_putstr_fd("/", 1);
	else
		ft_putstr_fd(tokens[i - 1], 1);
	ft_ansi_escape(0);
	ft_putstr_fd(" > ", 1);
	free(pwd);
	ft_strsfree(tokens);
}

// 로그인 메시지를 출력함.
void			ft_loginmsg(char *file)
{
	char		*msg;
	int			len;

	msg = ft_msgstr(file);
	if (msg == NULL)
		return ;
	len = ft_strlen(msg);
	ft_putstr_fd(msg, 1);
}

// 로그인 메시지 가져옴.
char			*ft_msgstr(char *file)
{
	char		*rtn;
	char		*line;
	char		*bp;
	int			gnl;
	int			fd;

	fd = ft_getfd(file, 'r');
	if (fd < 1)
		return (NULL);
	bp = NULL;
	rtn = NULL;
	while (1)
	{
		gnl = ft_get_next_line(fd, &line, &bp);
		line = ft_strnstack(line, "\n", 1);
		rtn = ft_strnstack(rtn, line, ft_strlen(line));
		if (gnl == 0)
			break;
	}
	close(fd);
	return (rtn);
}

void			ft_ansi_escape(int i)
{
	if (i == 0)
		ft_putstr_fd("\033[0m",  1);
	if (i == 1)
		ft_putstr_fd("\033[1;90m",  1);
	if (i == 2)
		ft_putstr_fd("\033[1;91m",  1);
	if (i == 3)
		ft_putstr_fd("\033[1;92m",  1);
	if (i == 4)
		ft_putstr_fd("\033[1;93m",  1);
	if (i == 5)
		ft_putstr_fd("\033[1;94m",  1);
	if (i == 6)
		ft_putstr_fd("\033[1;95m",  1);
	if (i == 7)
		ft_putstr_fd("\033[1;96m",  1);
	if (i == 8)
		ft_putstr_fd("\033[1;97m",  1);
}
