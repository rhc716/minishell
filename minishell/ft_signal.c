/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:02:14 by joopark           #+#    #+#             */
/*   Updated: 2021/03/02 17:52:07 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// signal에 콜백함수 등록
void			ft_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigkill);
}

// ctrl + c (현재는 이벤트만 받음. 보완해야함)
void			ft_sigint(int code)
{
	(void) code;
	ft_putstr_fd("\b\b  \b\b", 1);
	ft_prompt();
}

// ctrl + \ (현재는 이벤트만 받음. 보완해야함)
void			ft_sigkill(int code)
{
	(void) code;
	ft_putstr_fd("\b\b  \b\b", 1);
}
