/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:51:19 by hroh              #+#    #+#             */
/*   Updated: 2021/02/24 17:15:12 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// 배열의 첫번째 요소인 builtin 함수를 실행
void ft_exec_builtins(char **arg, char *envp[])
{
	int status;

	if (!ft_strncmp(arg[0], "cd", 3))
		ft_cd(arg);
	else if (!ft_strncmp(arg[0], "echo", 5))
		ft_echo(arg);
	else if (!ft_strncmp(arg[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(arg[0], "env", 4))
		ft_env(arg, envp);
	else if (!ft_strncmp(arg[0], "export", 7))
		ft_export(arg);
	else if (!ft_strncmp(arg[0], "unset", 6))
		ft_unset(arg);
	else if (!ft_strncmp(arg[0], "exit", 5))
		ft_exit("builtin exit", status);
	else
		return (0);
	return (1);
}

// 문자열이 builtin 함수인지 검사
int ft_check_builtins(char *cmd)
{
	if (!ft_strncmp(cmd, "cd", 3) || !ft_strncmp(cmd, "echo", 5)
	|| !ft_strncmp(cmd, "pwd", 4) || !ft_strncmp(cmd, "env", 4)
	|| !ft_strncmp(cmd, "export", 7) || !ft_strncmp(cmd, "unset", 6)
	|| !ft_strncmp(cmd, "exit", 5))
		return (1);
	return (0);
}