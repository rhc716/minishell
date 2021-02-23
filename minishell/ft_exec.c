/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:33:02 by joopark           #+#    #+#             */
/*   Updated: 2021/02/18 22:48:16 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t			ft_exec(char *file, char *argv[], char *envp[])
{
	pid_t		rtn;

	rtn = fork();
	if (rtn == 0)
		execve(file, argv, envp);
	return (rtn);
}

int				ft_isexecutable(char *file)
{
	struct stat	test;

	if (stat(file, &test) != -1)
		return (1);
	else
		return (0);
}

char			*ft_find_exec(char *envp[], char *cmd)
{
	char		*rtn;
	char		**paths;
	char		*pathtmp;
	char		*pathtmp1;
	int			j;
	
	j = 0;
	rtn = NULL;
	paths = ft_split(ft_getenv(envp, "PATH"), ':');
	if (paths == NULL)
		return (NULL);
	while (paths[j] != NULL)
	{
		pathtmp1 = ft_strjoin(paths[j], "/");
		pathtmp = ft_strjoin(pathtmp1, cmd);
		if (ft_isexecutable(pathtmp) == 1 && rtn == NULL)
			rtn = pathtmp;
		else
			free(pathtmp);
		free(pathtmp1);
		free(paths[j]);
		j++;
	}
	free(paths[j]);
	return (rtn);
}
