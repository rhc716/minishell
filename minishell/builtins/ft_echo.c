/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:17 by hroh              #+#    #+#             */
/*   Updated: 2021/02/27 17:26:55 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// -n 옵션인지 체크, -nnn...n 도 동일
int		ft_check_option_n(char *arg)
{
	int	i;

	if (ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	i = 2;
	while (arg[i])
		if (arg[i++] != 'n')
			return (0);
	return (1);
}

// 환경변수 출력, 및 echo $? 출력
void	ft_echo_env(char *env_key, char *envp[])
{
	if (*env_key == '?')
		ft_putstr_fd("exit_status", 1); // 추가 필요
	if (*env_key != '?')
		ft_putstr_fd(ft_getenv(envp, env_key), 1);
}

void	ft_echo(char **arg, char *envp[])
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if ((option_n = ft_check_option_n(arg[1])) == 1)
		i++;
	while (arg[i])
	{
		if (arg[i][0] == '$')
			ft_echo_env(arg[i] + 1, envp);
		else
			ft_putstr_fd(arg[i], 1);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (option_n != 1)
		ft_putchar_fd('\n', 1);
}
