/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:51:19 by hroh              #+#    #+#             */
/*   Updated: 2021/03/04 15:22:43 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		ft_exit_call_2(char **arg, int fd[])
{
	int i;

	i = -1;
	if (arg[1] == NULL && fd[1] == STDOUT_FILENO)
		ft_exit("exit\n", EXIT_SUCCESS);
	while (arg[1] && arg[1][++i])
	{
		if (ft_isdigit(arg[1][i]) == 0)
		{
			if (fd[1] == STDOUT_FILENO)
				ft_putstr_fd("exit\n", STDERR_FILENO);
			ft_put_err_msg("minishell: exit: ", arg[1],
			": numeric argument required\n", STDERR_FILENO);
			if (fd[1] == STDOUT_FILENO)
				ft_exit("", 255);
			return (255);
		}
	}
	return (0);
}

int		ft_exit_call(char **arg, int fd[])
{
	if (ft_exit_call_2(arg, fd) == 255)
		return (255);
	if (arg[1] && arg[2])
	{
		if (fd[1] == STDOUT_FILENO)
			ft_putstr_fd("exit\n", STDERR_FILENO);
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		return (1);
	}
	else if (fd[1] == STDOUT_FILENO)
		ft_exit("exit\n", ft_atoi(arg[1]));
	return (0);
}

void	ft_exec_builtins(char **arg, char **envp[], int fd[], t_com *com)
{
	if (!ft_strncmp(arg[0], "cd", 3))
		com->status = ft_cd(arg, envp, fd);
	else if (!ft_strncmp(arg[0], "echo", 5))
		com->status = ft_echo(arg, *envp, fd, com);
	else if (!ft_strncmp(arg[0], "pwd", 4))
		com->status = ft_pwd(fd);
	else if (!ft_strncmp(arg[0], "env", 4))
		com->status = ft_env(*envp, fd);
	else if (!ft_strncmp(arg[0], "export", 7))
		com->status = ft_export(arg, envp, fd);
	else if (!ft_strncmp(arg[0], "unset", 6))
		com->status = ft_unset(arg, envp, fd);
	else if (!ft_strncmp(arg[0], "exit", 5))
		com->status = ft_exit_call(arg, fd);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
	{
		com->status = 0;
		close(fd[1]);
	}
}

int		ft_check_builtins(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
	|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "env", 4)
	|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)
	|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}
