/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 01:45:32 by joopark           #+#    #+#             */
/*   Updated: 2021/03/05 12:06:12 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				main(int argc, char *argv[], char *envp[])
{
	char		**env;
	char		*bp;
	char		*line;

	(void)argc;
	(void)argv;
	g_status = 0;
	ft_signal();
	env = ft_strsdup(envp);
	bp = NULL;
	ft_loginmsg("./prompt");
	ft_putstr_fd("\n", STDOUT_FILENO);
	while (1)
	{
		ft_prompt();
		line = ft_getline(&bp);
		ft_run(line, &env);
		free(line);
	}
	return (0);
}
