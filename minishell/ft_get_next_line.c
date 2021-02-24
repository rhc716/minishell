/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 20:43:13 by joopark           #+#    #+#             */
/*   Updated: 2021/02/24 13:34:55 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// 42 과제 gnl과 동일하므로 별도로 수정할 필요 없음.
char				*ft_getbuf(ssize_t clr, char **bp)
{
	if (*bp == NULL)
	{
		if (!(*bp = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
			return (NULL);
		ft_memset(*bp, 0, BUFFER_SIZE + 1);
	}
	if (*bp != NULL && clr == 0)
	{
		free(*bp);
		*bp = NULL;
	}
	return (*bp);
}

int					ft_prechk(int fd, char **line, char **bufrtn, char **bp)
{
	char			tmp;

	if (fd < 0)
		return (-1);
	if (read(fd, &tmp, 0) == -1)
		return (-1);
	if (BUFFER_SIZE < 1)
		return (-1);
	if (line == NULL)
		return (-1);
	if (!(*line = ft_strnstack(NULL, "", 0)))
		return (-1);
	if (!(*bufrtn = ft_getbuf(1, bp)))
		return (-1);
	return (0);
}

int					ft_get_next_line(int fd, char **line, char **bp)
{
	ssize_t			len;
	char			*p;
	char			*b;

	len = -2;
	if (ft_prechk(fd, line, &b, bp) == -1)
		return (-1);
	while ((len != -1 && len != 0))
	{
		if (ft_strlen(b) == 0)
			len = read(fd, b, BUFFER_SIZE);
		else
		{
			p = ft_strnstr(b, "\n", BUFFER_SIZE);
			if (!(*line = ft_strnstack(*line, b, p ? (p - b) : ft_strlen(b))))
				return (-1);
			ft_memcpy(b, p + 1, p ? (ft_strlen(p + 1) + 1) : 0);
			ft_memset(b + (p ? ft_strlen(b) : 0), 0,
				BUFFER_SIZE - (p ? ft_strlen(b) : 0));
			if (p)
				break ;
		}
	}
	b = ft_getbuf(len, bp);
	return ((len == -2 || len > 0 || (b != NULL && !len)) ? 1 : len);
}
