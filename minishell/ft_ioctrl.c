/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:34:53 by joopark           #+#    #+#             */
/*   Updated: 2021/02/25 23:50:55 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
