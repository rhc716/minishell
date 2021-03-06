/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:21 by hroh              #+#    #+#             */
/*   Updated: 2021/03/03 16:40:56 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_env(char *envp[], int fd[])
{
	int i;

	i = 0;
	while (envp[i])
		ft_putendl_fd(envp[i++], fd[1]);
	return (0);
}
