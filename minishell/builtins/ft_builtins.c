/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 15:51:19 by hroh              #+#    #+#             */
/*   Updated: 2021/02/27 18:45:03 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// ft_exit를 호출시 인자에 따라 처리
// 1. 인자가 없을때 EXIT_SUCCESS로 호출
// 2. 첫번째 인자가 숫자가 아닌경우 : 종료 및 에러문구 status=255 : 맥에서 테스트시
// 3. 첫번째 인자가 숫자이고 인자가 2개 이상 : 종료하지 않고 에러문구
// 4. 인자가 1개이고 숫자
void	ft_exit_call(char **arg)
{
	int i;

	i = -1;
	if (arg[1] == NULL)
		ft_exit("exit\n", EXIT_SUCCESS);
	while (arg[1][++i])
	{
		if (ft_isdigit(arg[1][i]) == 0)
		{
			ft_putstr_fd("exit: ", 1);
			ft_putstr_fd(arg[1], 1);
			ft_exit(": numeric argument required\n", 255);
		}
	}
	if (arg[2])
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 1);
		return ;
	}
	else
		ft_exit("exit\n", ft_atoi(arg[1]));
}

// 배열의 첫번째 요소인 builtin 함수를 실행
int		ft_exec_builtins(char **arg, char **envp[])
{
	if (!ft_strncmp(arg[0], "cd", 3))
		ft_cd(arg, *envp);
	else if (!ft_strncmp(arg[0], "echo", 5))
		ft_echo(arg, *envp);
	else if (!ft_strncmp(arg[0], "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(arg[0], "env", 4))
		ft_env(*envp);
	else if (!ft_strncmp(arg[0], "export", 7))
		ft_export(arg, envp);
	else if (!ft_strncmp(arg[0], "unset", 6))
		ft_unset(arg, envp);
	else if (!ft_strncmp(arg[0], "exit", 5))
		ft_exit_call(arg);
	else
		return (0);
	return (1);
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
