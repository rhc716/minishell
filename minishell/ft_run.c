/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:22:59 by joopark           #+#    #+#             */
/*   Updated: 2021/03/07 19:28:16 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_run(char *cmd, char **envp[])
{
	char		**cmds;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, ';', (char)0xff);
	cmds = ft_parse_split(cmd, ';', (char)0xff, ';');
	while (cmds[i] != NULL)
	{
		ft_run_with_pipe(cmds[i], envp);
		i++;
	}
	ft_strsfree(cmds);
}

void			ft_run_with_pipe(char *cmd, char **envp[])
{
	pid_t		*pids;
	char		**cmds;
	int			**pipes;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, '|', (char)0xff);
	cmds = ft_parse_split(cmd, '|', (char)0xff, '|');
	while (cmds[i] != NULL)
		i++;
	pids = malloc(sizeof(pid_t) * i);
	pipes = ft_genpipes(i);
	i = 0;
	while (cmds[i] != NULL)
	{
		pids[i] = ft_run_cmd(cmds[i], envp, pipes[i]);
		i++;
	}
	g_status = ft_exec_wait(pids, i);
	ft_closepipe(pipes, i);
	ft_strsfree(cmds);
}

pid_t			ft_run_cmd(char *cmd, char **envp[], int io[])
{
	pid_t		rtn;
	char		*tmp;
	char		**arg;
	int			ioerr[3];

	tmp = ft_parse_replace_inquote(ft_strdup(cmd), ' ', (char)0xff);
	tmp = ft_ext_iofd(tmp, &ioerr[0], &ioerr[1], &ioerr[2]);
	arg = ft_parse_split(tmp, ' ', (char)0xff, ' ');
	arg = ft_quote_remove_list(arg);
	free(tmp);
	io[0] = (ioerr[0] > 0) ? ioerr[0] : io[0];
	io[1] = (ioerr[1] > 0) ? ioerr[1] : io[1];
	if (arg == NULL)
		rtn = 0;
	if (ioerr[2] == 0)
		rtn = ft_run_exec(arg, envp, io);
	else
		rtn = -1;
	if (ioerr[0] > 0)
		close(ioerr[0]);
	if (ioerr[1] > 0)
		close(ioerr[1]);
	ft_strsfree(arg);
	return (rtn);
}

pid_t			ft_run_exec(char *args[], char **envp[], int io[])
{
	char		*exec;
	pid_t		rtn;

	rtn = 0;
	if (args[0] != NULL && ft_check_builtins(args[0]) == 1)
		ft_exec_builtins(args, envp, io);
	else
	{
		exec = ft_find_exec(*envp, args[0]);
		if (exec != NULL)
			rtn = ft_exec(exec, args, *envp, io);
		else
		{
			ft_put_err_msg("minishell: ", args[0], NULL, 2);
			rtn = (args[0] && ft_isexecutable(args[0]) == 2) ? -126 : -127;
			if (args[0] == NULL || ft_strrchr(args[0], '/') == NULL)
				ft_put_err_msg(NULL, NULL, ": command not found\n", 2);
			else if (ft_isexecutable(args[0]) == 2)
				ft_put_err_msg(NULL, NULL, ": is a directory\n", 2);
			else
				ft_put_err_msg(NULL, NULL, ": No such file or directory\n", 2);
		}
		free(exec);
	}
	return (rtn);
}
