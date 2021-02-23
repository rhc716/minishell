/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:14:27 by joopark           #+#    #+#             */
/*   Updated: 2021/02/18 22:45:50 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_getenv(char *envp[], char *key)
{
	int			i;

	i = 0;
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, 4) == 0)
		{
			return (envp[i] + ft_strlen(key) + 1);
		}
		i++;
	}
	return (NULL);
}