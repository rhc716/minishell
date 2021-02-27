/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:36:56 by hroh              #+#    #+#             */
/*   Updated: 2021/02/27 17:25:06 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stdio.h>

// 이동 성공시 pwd, old pwd 변경
void	ft_export_pwd(char *envp[], char *old_pwd)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_export_arg("PWD", pwd, &envp);
	ft_export_arg("OLDPWD", old_pwd, &envp);
	free(pwd);
}

// 환경변수에 저장된 home으로 이동
void	ft_cd_home(char *envp[], char *old_pwd)
{
	char	*path;

	path = ft_getenv(envp, "HOME");
	if (chdir(path) == 0)
		ft_export_pwd(envp, old_pwd);
	else
		printf("cd error : There is no $HOME in env.\n"); // error
}

// 환경변수에 저장된 경로로 이동, 실패시 home으로
void	ft_cd_env(char *path, char *envp[], char *old_pwd)
{
	char	*env_val;

	env_val = ft_getenv(envp, &path[1]);
	if (chdir(env_val) == 0)
		ft_export_pwd(envp, old_pwd);
	else
		ft_cd_home(envp, old_pwd);
}

// 상대경로 및 절대경로 이동
void	ft_cd_path(char *path, char *envp[], char *old_pwd)
{
	if (chdir(path) == 0)
		ft_export_pwd(envp, old_pwd);
	else
		printf("strerror(2)\n"); // error
}

// 이동 성공시 이동한 경로에 맞게 pwd oldpwd 환경변수 수정
void	ft_cd(char **arg, char *envp[])
{
	char	*path;
	char	*old_pwd;

	path = arg[1];
	old_pwd = getcwd(NULL, 0);
	if (path != NULL && path[0] != '~' && path[0] != '$')
		ft_cd_path(path, envp, old_pwd);
	else if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		ft_cd_home(envp, old_pwd);
	else if (path[0] == '$')
		ft_cd_env(path, envp, old_pwd);
	else
		printf("strerror(2)\n"); // error
	free(old_pwd);
}
