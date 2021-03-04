/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_console.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/01 14:21:07 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 15:35:53 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_prompt(void)
{
	char		*pwd;
	char		**tokens;
	int			i;

	i = 0;
	ft_putstr_fd("\n$ ", STDOUT_FILENO);
	pwd = getcwd(NULL, 0);
	tokens = ft_split(pwd, '/');
	ft_ansi_escape(5, STDOUT_FILENO);
	while (tokens[i] != NULL)
		i++;
	if (i == 0)
		ft_putstr_fd("/", STDOUT_FILENO);
	else
		ft_putstr_fd(tokens[i - 1], STDOUT_FILENO);
	ft_ansi_escape(0, STDOUT_FILENO);
	ft_putstr_fd(" > ", STDOUT_FILENO);
	free(pwd);
	ft_strsfree(tokens);
}

void			ft_loginmsg(char *file)
{
	char		*msg;
	int			len;

	msg = ft_msgstr(file);
	if (msg == NULL)
		return ;
	len = ft_strlen(msg);
	ft_putstr_fd(msg, STDOUT_FILENO);
	free(msg);
}

char			*ft_msgstr(char *file)
{
	char		*rtn;
	char		buf[BUFFER_SIZE];
	int			len;
	int			fd;

	fd = ft_getfd(file, 'r');
	if (fd < 1)
		return (NULL);
	rtn = NULL;
	while (1)
	{
		len = read(fd, buf, BUFFER_SIZE);
		rtn = ft_strnstack(rtn, buf, len);
		if (len == -1 || len < BUFFER_SIZE)
			break ;
	}
	close(fd);
	return (rtn);
}

void			ft_ansi_escape(int i, int fd)
{
	if (i == 0)
		ft_putstr_fd("\033[0m", fd);
	if (i == 1)
		ft_putstr_fd("\033[1;90m", fd);
	if (i == 2)
		ft_putstr_fd("\033[1;91m", fd);
	if (i == 3)
		ft_putstr_fd("\033[1;92m", fd);
	if (i == 4)
		ft_putstr_fd("\033[1;93m", fd);
	if (i == 5)
		ft_putstr_fd("\033[1;94m", fd);
	if (i == 6)
		ft_putstr_fd("\033[1;95m", fd);
	if (i == 7)
		ft_putstr_fd("\033[1;96m", fd);
	if (i == 8)
		ft_putstr_fd("\033[1;97m", fd);
}
