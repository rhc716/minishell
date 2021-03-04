/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_run.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/26 12:22:59 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 22:24:51 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			ft_run(char *cmd, char **envp[], t_com *com)
{
	char		**cmds;
	int			i;

	i = 0;
	cmd = ft_parse_replace_inquote(cmd, ';', (char)0xff);
	cmds = ft_parse_split(cmd, ';', (char)0xff, ';');
	while (cmds[i] != NULL)
	{
		ft_run_with_pipe(cmds[i], envp, com);
		i++;
	}
	ft_strsfree(cmds);
}

void			ft_run_with_pipe(char *cmd, char **envp[], t_com *com)
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
		pids[i] = ft_run_cmd(cmds[i], envp, pipes[i], com);
		i++;
	}
	com->status = ft_exec_wait(pids, i);
	ft_closepipe(pipes, i);
	ft_strsfree(cmds);
}

pid_t			ft_run_cmd(char *cmd, char **envp[], int io[], t_com *com)
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
	if (ioerr[2] == 0)
		rtn = ft_run_exec(arg, envp, io, com);
	else
		rtn = -1;
	if (ioerr[0] > 0)
		close(ioerr[0]);
	if (ioerr[1] > 0)
		close(ioerr[1]);
	ft_strsfree(arg);
	return (rtn);
}

pid_t			ft_run_exec(char *args[], char **envp[], int io[], t_com *com)
{
	char		*exec;
	pid_t		rtn;
	int			stat_loc;

	stat_loc = -1;
	rtn = 0;
	if (args != NULL)
	{
		if (args[0] != NULL && ft_check_builtins(args[0]) == 1)
			ft_exec_builtins(args, envp, io, com);
		else
		{
			exec = ft_find_exec(*envp, args[0]);
			if (exec != NULL)
				rtn = ft_exec(exec, args, *envp, io);
			else
			{
				ft_put_err_msg("minishell: ", args[0],
					": No such file or directory\n", STDERR_FILENO);
				rtn = -127;
			}
			free(exec);
		}
	}
	return (rtn);
}
