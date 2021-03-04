/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 13:38:29 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 15:38:43 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_exit(char *msg, int status)
{
	if (msg != NULL)
		ft_putstr_fd(msg, STDOUT_FILENO);
	exit(status);
}
