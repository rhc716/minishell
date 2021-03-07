/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:29 by hroh              #+#    #+#             */
/*   Updated: 2021/03/08 04:01:34 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_exec(char *arg, char **envp[])
{
	char **temp;

	if (ft_getenv(*envp, arg) != NULL &&
		(temp = ft_clearenv(*envp, arg)) != NULL)
	{
		ft_strsfree(*envp);
		*envp = temp;
	}
}

int		ft_unset(char **arg, char **envp[], int fd[])
{
	int		i;
	int		ret;
	char	*temp;
	char	*p;

	i = 0;
	ret = 0;
	while (arg[++i])
	{
		temp = ft_strdup(arg[i]);
		if ((p = ft_strchr(arg[i], '$')) && *(p + 1) != '\0')
			temp = ft_replace_env_in_arg(temp, p, *envp, 1);
		if (ft_strlen(temp) && ft_isvalid_key(temp) != 1)
			ret = ft_put_err_msg("minishell: unset: \'", temp,
			"\': not an identifier\n", STDERR_FILENO);
		else if (fd[1] == STDOUT_FILENO)
			ft_unset_exec(temp, envp);
		free(temp);
	}
	return (ret);
}
