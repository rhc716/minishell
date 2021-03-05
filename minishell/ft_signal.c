/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:02:14 by joopark           #+#    #+#             */
/*   Updated: 2021/03/05 12:31:04 by joopark          ###   ########.fr       */
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
	int			stat_loc;
	pid_t		pid;

	(void)code;
	pid = wait3(&stat_loc, 0, NULL);
	if (pid == -1)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		ft_prompt();
		g_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_status = 130;
	}
}

void			ft_sigkill(int code)
{
	int			stat_loc;
	pid_t		pid;

	(void)code;
	pid = wait3(&stat_loc, 0, NULL);
	if (pid == -1)
	{
		ft_putstr_fd("\b\b  \b\b", STDOUT_FILENO);
	}
	else
	{
		ft_putstr_fd("Quit: ", STDOUT_FILENO);
		ft_putnbr_fd(stat_loc, STDOUT_FILENO);
		ft_putstr_fd("\n", STDOUT_FILENO);
		g_status = 131;
	}
}
