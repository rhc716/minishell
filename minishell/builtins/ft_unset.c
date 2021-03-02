/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:29 by hroh              #+#    #+#             */
/*   Updated: 2021/03/02 18:18:06 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset(char **arg, char **envp[], int fd[])
{
	int		i;
	int		j;
	char	**tmp;

	if (fd[1] != STDOUT_FILENO)
		return ;
	i = 1;
	while (arg[i])
	{
		j = 0;
		while (arg[i][j])
		{
			if (!ft_isalpha(arg[i][j]) && !ft_isdigit(arg[i][j])
				&& arg[i][j] != '_')
				return ;
			j++;
		}
		if ((tmp = ft_clearenv(*envp, arg[i])) != NULL)
		{
			ft_strsfree(*envp);
			*envp = tmp;
		}
		i++;
	}
}
