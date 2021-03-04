/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 22:14:27 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 15:54:32 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_getenv(char *envp[], char *key)
{
	int			i;
	int			len;

	i = 0;
	len = ft_strlen(key);
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + ft_strlen(key) + 1);
		i++;
	}
	return (NULL);
}

char			**ft_setenv(char *envp[], char *key, char *value)
{
	if (ft_getenv(envp, key) == NULL)
		return (ft_newenv(envp, key, value));
	else
		return (ft_modenv(envp, key, value));
}

char			**ft_modenv(char *envp[], char *key, char *value)
{
	int			i;
	int			len;
	char		*newval;

	i = 0;
	len = ft_strlen(key);
	newval = ft_strjoin(key, "=");
	newval = ft_strnstack(newval, value, ft_strlen(value));
	while (envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
		{
			free(envp[i]);
			envp[i] = newval;
		}
		i++;
	}
	return (envp);
}

char			**ft_newenv(char *envp[], char *key, char *value)
{
	int			i;
	char		**rtn;
	char		*newval;

	i = 0;
	newval = ft_strjoin(key, "=");
	newval = ft_strnstack(newval, value, ft_strlen(value));
	while (envp[i] != NULL)
		i++;
	rtn = malloc(sizeof(char *) * (i + 2));
	if (rtn == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		rtn[i] = ft_strdup(envp[i]);
		i++;
	}
	rtn[i] = newval;
	rtn[i + 1] = NULL;
	return (rtn);
}

char			**ft_clearenv(char *envp[], char *key)
{
	int			i;
	int			j;
	int			len;
	char		**rtn;

	i = 0;
	if (ft_getenv(envp, key) == NULL)
		return (envp);
	while (envp[i] != NULL)
		i++;
	rtn = malloc(sizeof(char *) * i);
	if (rtn == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (envp[++i] != NULL)
	{
		len = 0;
		while (envp[i][len] != '\0' && envp[i][len] != '=')
			len++;
		if (!(ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '='))
			rtn[++j] = ft_strdup(envp[i]);
	}
	rtn[++j] = NULL;
	return (rtn);
}
