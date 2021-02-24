/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:36:56 by hroh              #+#    #+#             */
/*   Updated: 2021/02/24 20:23:30 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

void ft_cd(char **arg, char *envp[])
{
	// 테스트용도
	printf("func : %s\n", __func__);
	int i = -1;
	while (arg[++i])
		printf("arg[%d] : %s\n", i, arg[i]);
	// 테스트용도
	char	*path;
	int		ret;

	path = 0;
	ret = 0;
	if (arg[1][0] != '~' && arg[1] != NULL && arg[1][0] != '$')
	{
		path = arg[1];
		if (chdir(path) == -1)
			return ; // error
		// 바뀐 경로로 pwd export
	}
	//else if (arg[1][0] == '~' || arg[1] == NULL)
	//	ft_cd_home(path, envp);
	//else if (arg[1][0] == '$')
	//	ft_cd_env(path, envp);
}