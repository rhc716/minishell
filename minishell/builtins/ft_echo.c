/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:38:17 by hroh              #+#    #+#             */
/*   Updated: 2021/03/08 01:08:56 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	ft_echo_env(char *env_key, char *envp[], int fd[])
{
	if (*env_key == '?')
		ft_putnbr_fd(g_status, fd[1]);
	if (*env_key != '?')
		ft_putstr_fd(ft_getenv(envp, env_key), fd[1]);
}

void	ft_echo_print(int i, char **arg, char *envp[], int fd[])
{
	char	*temp;
	char	*p;

	if (arg[i][0] == '$' && arg[i][1] == '\0')
		ft_putchar_fd('$', fd[1]);
	else if (arg[i][0] == '$' && arg[i][1] &&
		ft_strrchr(arg[i], '$') == &arg[i][0])
		ft_echo_env(arg[i] + 1, envp, fd);
	else if ((p = ft_strchr(arg[i], '$')) && *(p + 1) != '\0')
	{
		temp = ft_replace_env_in_arg(arg[i], p, envp, 0);
		ft_putstr_fd(temp, fd[1]);
		free(temp);
	}
	else
		ft_putstr_fd(arg[i], fd[1]);
}

int		ft_echo(char **arg, char *envp[], int fd[])
{
	int	i;
	int	option_n;

	i = 1;
	option_n = 0;
	if (arg[1] && (option_n = ft_check_option_n(arg[1])) == 1)
		i++;
	while (arg[i])
	{
		ft_echo_print(i, arg, envp, fd);
		if (arg[i + 1] != NULL)
			ft_putchar_fd(' ', fd[1]);
		i++;
	}
	if (option_n != 1)
		ft_putchar_fd('\n', fd[1]);
	return (0);
}
