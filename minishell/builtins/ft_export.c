/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:24 by hroh              #+#    #+#             */
/*   Updated: 2021/03/04 13:52:04 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 인자가 없을 때 : env 배열을 아스키 순서로 정렬해서 출력
int		ft_export_no_arg(char *envp[], int fd[])
{
	char	**temp;
	int		i;

	temp = ft_strsdup(envp);
	i = -1;
	while (temp[++i])
		temp[i] = ft_strjoin_free("declare -x ", temp[i], 2);
	ft_sort_2d_arr(temp);
	ft_env(temp, fd);
	ft_strsfree(temp);
	return (0);
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
int		ft_export_arg(char *key, char *val, char **envp[], int fd[])
{
	char **tmp;

	if (ft_isvalid_key(key) == 0)
		return (0);
	if (fd[1] != STDOUT_FILENO)
		return (1);
	if (ft_getenv(*envp, key) == NULL)
	{
		if ((tmp = ft_setenv(*envp, key, val)) != NULL)
		{
			ft_strsfree(*envp);
			*envp = tmp;
		}
	}
	else
	{
		if ((tmp = ft_setenv(*envp, key, val)) != NULL)
			*envp = tmp;
	}
	return (1);
}

void	ft_set_key_val_sp(char **key, char **val, char *arg, char **sp)
{
	*key = ft_strdup(arg);
	*val = NULL;
	if ((*sp = ft_strchr(*key, '=')) != NULL)
	{
		**sp = '\0';
		*val = *sp + 1;
	}
}

int		ft_export(char **arg, char **envp[], int fd[])
{
	char	*key;
	char	*val;
	char	*sp;
	int		i;

	if (arg[1] == NULL)
		return (ft_export_no_arg(*envp, fd));
	i = 0;
	while (arg[++i])
	{
		ft_set_key_val_sp(&key, &val, arg[i], &sp);
		if (ft_isvalid_key(key) == 0 ||
			(sp != NULL &&
			(val == NULL || ft_export_arg(key, val, envp, fd) == 0)))
		{
			ft_put_err_msg("minishell: export: \'",
			arg[i], "\': not an identifier\n", STDERR_FILENO);
			free(key);
			return (1);
		}
		free(key);
	}
	return (0);
}
