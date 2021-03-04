/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:02:14 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 16:42:31 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_signal(void)
{
	signal(SIGINT, ft_sigint);
	signal(SIGQUIT, ft_sigkill);
}

void			ft_sigint(int code)
{
	(void)code;
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_prompt();
}

void			ft_sigkill(int code)
{
	(void)code;
	ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
}
