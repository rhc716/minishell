/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ioctrl.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 16:34:53 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 15:14:22 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_getfd(char *filename, char mode)
{
	int			rtn;

	if (mode == 'r')
		rtn = open(filename, O_RDONLY);
	else if (mode == 'w')
		rtn = open(filename, O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG);
	else if (mode == '+')
		rtn = open(filename, O_APPEND | O_WRONLY | O_CREAT, S_IRWXU | S_IRWXG);
	else
		rtn = 0;
	if (rtn == -1)
	{
		rtn *= errno;
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(filename, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
	}
	return (rtn);
}

char			*ft_ext_iofd(char *cmd, int *i, int *o, int *err)
{
	char		*in;
	char		*out;
	char		rp;

	cmd = ft_parse_redirect(cmd, &in, &out, &rp);
	*i = 0;
	*o = 0;
	if (in != NULL)
		*i = ft_getfd(in, 'r');
	if (out != NULL && rp == 'w')
		*o = ft_getfd(out, 'w');
	if (out != NULL && rp == '+')
		*o = ft_getfd(out, '+');
	if (*i < 0)
		*err = *i;
	else if (*o < 0)
		*err = *o;
	else
		*err = 0;
	if (in != NULL)
		free(in);
	if (out != NULL)
		free(out);
	return (cmd);
}

int				**ft_genpipes(int len)
{
	int			**rtn;
	int			i;

	i = 0;
	rtn = malloc(sizeof(int *) * len);
	if (rtn == NULL)
		return (NULL);
	while (i < len)
	{
		rtn[i] = malloc(sizeof(int) * 2);
		if (rtn[i] == NULL)
			return (NULL);
		if (i == 0)
			rtn[i][0] = STDIN_FILENO;
		if ((i + 1) == len)
			rtn[i][1] = STDOUT_FILENO;
		if (i > 0)
		{
			if (ft_genpipe(&rtn[i - 1][1], &rtn[i][0]) == -1)
				return (NULL);
		}
		i++;
	}
	return (rtn);
}

int				ft_genpipe(int *i, int *o)
{
	int			io[2];
	int			rtn;

	rtn = pipe(io);
	*i = io[1];
	*o = io[0];
	return (rtn);
}

void			ft_closepipe(int **pipe, int len)
{
	while (--len >= 0)
	{
		if (pipe[len][0] != STDIN_FILENO)
			close(pipe[len][0]);
		if (pipe[len][1] != STDOUT_FILENO)
			close(pipe[len][1]);
		free(pipe[len]);
	}
	free(pipe);
}