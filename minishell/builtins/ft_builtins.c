/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:51:19 by hroh              #+#    #+#             */
/*   Updated: 2021/03/02 19:18:05 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ft_exit를 호출시 인자에 따라 처리
void	ft_exit_call(char **arg, int fd[])
{
	int i;

	i = -1;
	if (arg[1] == NULL && fd[1] == STDOUT_FILENO)
		ft_exit("exit\n", EXIT_SUCCESS);
	while (arg[1][++i])
	{
		if (ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
			ft_putstr_fd(arg[1], STDERR_FILENO);
			ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
			if (fd[1] == STDOUT_FILENO)
				ft_exit("", 255);
			return ;
		}
	}
	if (arg[2])
		ft_putstr_fd("exit\nminishell: exit: too many arguments\n", STDERR_FILENO);
	else if (fd[1] == STDOUT_FILENO)
		ft_exit("exit\n", ft_atoi(arg[1]));
}

// 배열의 첫번째 요소인 builtin 함수를 실행
void	ft_exec_builtins(char **arg, char **envp[], int fd[], t_com com)
{
	if (!ft_strncmp(arg[0], "cd", 3))
		ft_cd(arg, envp, fd);
	else if (!ft_strncmp(arg[0], "echo", 5))
		ft_echo(arg, *envp, fd);
	else if (!ft_strncmp(arg[0], "pwd", 4))
		ft_pwd(fd);
	else if (!ft_strncmp(arg[0], "env", 4))
		ft_env(*envp, fd);
	else if (!ft_strncmp(arg[0], "export", 7))
		ft_export(arg, envp, fd);
	else if (!ft_strncmp(arg[0], "unset", 6))
		ft_unset(arg, envp, fd);
	else if (!ft_strncmp(arg[0], "exit", 5))
		ft_exit_call(arg, fd);
	if (fd[0] != STDIN_FILENO)
		close(fd[0]);
	if (fd[1] != STDOUT_FILENO)
		close(fd[1]);
}

// 문자열이 builtin 함수인지 검사
int		ft_check_builtins(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
	|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "env", 4)
	|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)
	|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}
