/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:02:14 by joopark           #+#    #+#             */
/*   Updated: 2021/02/17 13:26:04 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void			ft_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigkill);
}

void			ft_sigint(int code)
{
	write(1, "\b\b", 2);
	printf("[SIGNAL] %d at %s\n", code, __func__);
}

void			ft_sigkill(int code)
{
	write(1, "\b\b", 2);
	printf("[SIGNAL] %d at %s\n", code, __func__);
}
