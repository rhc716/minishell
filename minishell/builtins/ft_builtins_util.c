/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:30:51 by hroh              #+#    #+#             */
/*   Updated: 2021/03/08 03:05:47 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

int		ft_put_err_msg(char *s1, char *s2, char *s3, int fd)
{
	ft_putstr_fd(s1, fd);
	ft_putstr_fd(s2, fd);
	ft_putstr_fd(s3, fd);
	return (1);
}

void	ft_unset_str(char *str, char **envp[])
{
	char	**tmp;

	if (ft_getenv(*envp, str) != NULL &&
		((tmp = ft_clearenv(*envp, str)) != NULL))
	{
		ft_strsfree(*envp);
		*envp = tmp;
	}
}

char	*ft_replace_env_in_arg(char *arg, char *p, char *envp[], int free_yn)
{
	char	**temp;
	char	*ret;
	int		i;

	ret = ft_strdup(arg);
	ret[ft_strlen(ret) - ft_strlen(p)] = '\0';
	temp = ft_split(arg, '$');
	i = 0;
	if (ret[0] == '\0')
		i = -1;
	while (temp[++i])
	{
		if (ft_getenv(envp, temp[i]))
			ret = ft_strjoin_free(ret, ft_getenv(envp, temp[i]), 1);
	}
	ft_strsfree(temp);
	if (free_yn == 1)
		free(arg);
	return (ret);
}
