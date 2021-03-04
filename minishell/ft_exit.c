/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:38:29 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 15:13:00 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 미니쉘 종료시 출력할 메시지와 종료 코드를 받아 종료함.
void			ft_exit(char *msg, int status)
{
	if (msg != NULL)
		ft_putstr_fd(msg, STDOUT_FILENO);
	exit(status);
}