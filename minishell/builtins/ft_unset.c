/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:29 by hroh              #+#    #+#             */
/*   Updated: 2021/03/04 15:23:27 by joopark          ###   ########.fr       */
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
	i = 0;
	while (arg[++i])
	{
		j = 0;
		if (ft_isvalid_key(arg[i]) != 1)
		{
			ft_put_err_msg("minishell: unset: \'", arg[i],
			"\': not an identifier\n", STDERR_FILENO);
			return (1);
		}
		if (ft_getenv(*envp, arg[i]) != NULL &&
			((tmp = ft_clearenv(*envp, arg[i])) != NULL))
		{
			ft_strsfree(*envp);
			*envp = tmp;
		}
	}
	return (0);
}
