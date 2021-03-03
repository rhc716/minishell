/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:29 by hroh              #+#    #+#             */
/*   Updated: 2021/03/03 16:40:04 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_unset(char **arg, char **envp[], int fd[])
{
	int		i;
	int		j;
	char	**tmp;

	if (fd[1] != STDOUT_FILENO)
		return (0);
	i = 1;
	while (arg[i])
	{
		j = 0;
		if (ft_isvalid_key(arg[i]) != 1)
		{
			ft_putstr_fd("minishell: unset: \'", STDERR_FILENO);
			ft_putstr_fd(arg[i], STDERR_FILENO);
			ft_putstr_fd("\': not an identifier\n", STDERR_FILENO);
			return (1);
		}
		if (ft_getenv(*envp, arg[i]) != NULL &&
			((tmp = ft_clearenv(*envp, arg[i])) != NULL))
		{
			ft_strsfree(*envp);
			*envp = tmp;
		}
		i++;
	}
	return (0);
}
