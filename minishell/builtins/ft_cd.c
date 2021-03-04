/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 16:36:56 by hroh              #+#    #+#             */
/*   Updated: 2021/03/04 15:22:56 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_export_pwd(char **envp[], char *old_pwd, int fd[])
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_export_arg("PWD", pwd, envp, fd);
	ft_export_arg("OLDPWD", old_pwd, envp, fd);
	free(pwd);
	free(old_pwd);
}

void	ft_cd_home(char **envp[], char *old_pwd, int fd[])
{
	char	*path;
	DIR		*dir;

	path = ft_getenv(*envp, "HOME");
	if ((dir = opendir(path)) != NULL)
	{
		if (fd[1] == STDOUT_FILENO)
		{
			if (chdir(path) == 0)
				ft_export_pwd(envp, old_pwd, fd);
		}
		closedir(dir);
	}
	else
		ft_putstr_fd("minishell: cd: There is no $HOME in env.\n",
		STDERR_FILENO);
}

void	ft_cd_env(char *path, char **envp[], char *old_pwd, int fd[])
{
	char	*env_val;
	DIR		*dir;

	env_val = ft_getenv(*envp, &path[1]);
	if (env_val && (dir = opendir(env_val)) != NULL)
	{
		if (fd[1] == STDOUT_FILENO)
		{
			if (chdir(env_val) == 0)
				ft_export_pwd(envp, old_pwd, fd);
		}
		closedir(dir);
	}
	else
		ft_cd_home(envp, old_pwd, fd);
}

int		ft_cd_path(char *path, char **envp[], char *old_pwd, int fd[])
{
	DIR	*dir;

	if ((dir = opendir(path)) != NULL)
	{
		if (fd[1] == STDOUT_FILENO)
		{
			if (chdir(path) == 0)
				ft_export_pwd(envp, old_pwd, fd);
		}
		closedir(dir);
		return (0);
	}
	else
	{
		ft_put_err_msg("minishell: cd: ", path,
		": No such file or directory\n", STDERR_FILENO);
		return (1);
	}
}

int		ft_cd(char **arg, char **envp[], int fd[])
{
	char	*path;
	char	*old_pwd;

	path = arg[1];
	old_pwd = getcwd(NULL, 0);
	if (path != NULL && path[0] != '~' && path[0] != '$')
		return (ft_cd_path(path, envp, old_pwd, fd));
	else if (path == NULL || (path[0] == '~' && path[1] == '\0'))
		ft_cd_home(envp, old_pwd, fd);
	else if (path[0] == '$')
		ft_cd_env(path, envp, old_pwd, fd);
	else
	{
		ft_put_err_msg("minishell: cd: ", path,
		": No such file or directory\n", STDERR_FILENO);
		free(old_pwd);
		return (1);
	}
	return (0);
}
