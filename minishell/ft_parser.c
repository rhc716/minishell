/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 00:08:50 by joopark           #+#    #+#             */
/*   Updated: 2021/02/21 22:30:53 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

int				ft_parse_path(char *cmd)
{
	(void) cmd;
	return (-1);
}

char			**ft_parse_exec(char *cmd)
{
	char		**rtn;
	int			i;
	int			j;
	
	i = 0;
	cmd = ft_remove_quote(cmd);
	rtn = ft_split(cmd, ' ');
	while (rtn[i] != NULL)
	{
		j = 0;
		while (rtn[i][j] != '\0')
		{
			if (rtn[i][j] == (char)0xff)
				rtn[i][j] = ' ';
				j++;
		}
		i++;
	}
	return (rtn);
}

char			*ft_remove_quote(char *cmd)
{
	int			i;
	char		c;

	i = 0;
	c = '\0';
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			if (c == '\0')
			{
				c = cmd[i];
				cmd[i] = ' ';
			}
			else if (c == cmd[i])
			{
				c = '\0';
				cmd[i] = ' ';
			}
		}
		else if (c != '\0' && cmd[i] == ' ')
			cmd[i] = (char)0xff;
		i++;
	}
	return (cmd);
}
