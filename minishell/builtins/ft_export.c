/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:24 by hroh              #+#    #+#             */
/*   Updated: 2021/03/08 03:59:42 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_export_no_arg(char *envp[], int fd[])
{
	char	**temp;
	char	*sp;
	char	*val;
	int		i;

	temp = ft_strsdup(envp);
	ft_unset_str("_", &temp);
	i = -1;
	while (temp[++i])
	{
		if ((sp = ft_strchr(temp[i], '=')) != NULL)
			*sp = '\0';
		if ((val = ft_getenv(envp, temp[i])) != NULL)
		{
			temp[i] = ft_strjoin_free("declare -x ", temp[i], 2);
			temp[i] = ft_strjoin_free(temp[i], "=\"", 1);
			temp[i] = ft_strjoin_free(temp[i], val, 1);
			temp[i] = ft_strjoin_free(temp[i], "\"", 1);
		}
	}
	ft_sort_2d_arr(temp);
	ft_env(temp, fd);
	ft_strsfree(temp);
	return (0);
}

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

char	*ft_set_key_val_sp(char **key, char **val, char *arg, char *envp[])
{
	char	*p;
	char	*sp;

	sp = NULL;
	if (arg[0] == '=' && arg[1] == '\0')
	{
		*key = ft_strdup("=");
		return (*key);
	}
	else
		*key = ft_strdup(arg);
	if (arg[0] != '=' && (sp = ft_strchr(*key, '=')) != NULL)
		*sp = '\0';
	if (sp != NULL && sp + 1 != NULL)
		*val = ft_strdup(sp + 1);
	else
		*val = NULL;
	if ((p = ft_strchr(*key, '$')) && *(p + 1) != '\0')
		*key = ft_replace_env_in_arg(*key, p, envp, 1);
	if (*val != NULL && (p = ft_strchr(*val, '$')) && *(p + 1) != '\0')
		*val = ft_replace_env_in_arg(*val, p, envp, 1);
	return (sp);
}

int		ft_export(char **arg, char **envp[], int fd[])
{
	char	*key;
	char	*val;
	char	*sp;
	int		i;
	int		ret;

	if (arg[1] == NULL)
		return (ft_export_no_arg(*envp, fd));
	i = 0;
	ret = 0;
	while (arg[++i])
	{
		sp = ft_set_key_val_sp(&key, &val, arg[i], *envp);
		if (!ft_isvalid_key(key) || !sp || !ft_export_arg(key, val, envp, fd))
		{
			if (key[0] != '\0' && !ft_isvalid_key(key))
				ret = ft_put_err_msg("minishell: export: \'",
				key, "\': not an identifier\n", STDERR_FILENO);
		}
		free(key);
		if (val != NULL)
			free(val);
	}
	return (ret);
}
