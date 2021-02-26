/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:24 by hroh              #+#    #+#             */
/*   Updated: 2021/02/26 21:09:37 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// 2차원 char 배열을 버블소트
void	ft_sort_2d_arr(char **arr)
{
	int		i;
	int		j;
	int		k;
	char	*temp;
 
	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[++j + 1])
		{
			k = -1;
			while (arr[j][++k] && arr[j + 1][k] && arr[j][k] >= arr[j + 1][k])
			{
				if (arr[j][k] > arr[j + 1][k])
				{
					temp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = temp;
					break ;
				}
			}
		}
	}
}

// 인자가 없을 때 : env 배열을 아스키 순서로 정렬해서 출력
void	ft_export_no_arg(char *envp[])
{
	char	**temp;
	int		i;

	i = 0;
	while (envp[i])
		i++;
	if (!(temp = (char **)malloc(sizeof(char *) * (i + 1))))
		return ;
	i = -1;
	while (envp[++i])
		temp[i] = ft_strdup(envp[i]);
	temp[i] = NULL;
	ft_sort_2d_arr(temp);
	ft_env(temp);
	free(temp);
}

// 추가 할 key 값이 가능한 값인지 검사 : 알파벳, 숫자, _로 구성, 숫자로만 구성하면 안됨
int		ft_isvalid_key(char *key)
{
	int	i;
	int	alp_or_under;

	i = -1;
	alp_or_under = 0;
	while (key[++i])
	{
		if (!ft_isalpha(key[i]) && !ft_isdigit(key[i]) && key[i] != '_')
			return (0);
		if (ft_isalpha(key[i]) || key[i] == '_')
			alp_or_under = 1;
	}
	if (alp_or_under == 0)
		return (0);
	return (1);
}

// 인자가 존재할 때 : 생성 또는 수정
void	ft_export_arg(char *key, char *val, char **envp[])
{
	char **tmp;

	if (ft_isvalid_key(key) == 0)
		return ;
	if ((tmp = ft_setenv(*envp, key, val)) != NULL)
		*envp = tmp;
}

// 주의사항 : export z=x=y : x=y가 저장
void	ft_export(char **arg, char **envp[])
{
	int		i;
	char	*argv;
	char	*key;
	char	*val;

	if (arg[1] == NULL)
		ft_export_no_arg(*envp);
	else
	{
		i = 0;
		while (arg[1][i] && arg[1][i] != '=')
			i++;
		if (i == (int)ft_strlen(arg[1]) || i == 0)
			return ;
		argv = ft_strdup(arg[1]);
		argv[i] = '\0';
		key = argv;
		val = argv + i + 1;
		if (val != NULL)
			ft_export_arg(key, val, envp);
		free(argv);
	}
}
