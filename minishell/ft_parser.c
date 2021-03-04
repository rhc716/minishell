/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 00:08:50 by joopark           #+#    #+#             */
/*   Updated: 2021/03/04 15:39:39 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ft_parse_split(char *str, char s, char c, char r)
{
	char		**rtn;
	int			i;
	int			j;

	i = 0;
	rtn = ft_split(str, s);
	while (rtn[i] != NULL)
	{
		j = 0;
		while (rtn[i][j] != '\0')
		{
			if (rtn[i][j] == c)
				rtn[i][j] = r;
			j++;
		}
		i++;
	}
	return (rtn);
}

char			*ft_parse_redirect(char *cmd, char **in, char **out, char *rp)
{
	int			i;
	char		q;

	i = 0;
	q = '\0';
	*in = NULL;
	*out = NULL;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'' || cmd[i] == '"')
		{
			if (q == '\0')
				q = cmd[i];
			else if (q == cmd[i])
				q = '\0';
			i++;
		}
		else if (q == '\0' && ((cmd[i] == '<') || (cmd[i] == '>')))
			i += ft_parse_get_name(&cmd[i], in, out, rp);
		else
			i++;
	}
	return (cmd);
}

int				ft_parse_get_name(char *cmd, char **in, char **out, char *rp)
{
	int			rtn;

	if (cmd[0] == '<')
	{
		cmd[0] = ' ';
		rtn = ft_getword(cmd, in);
	}
	else
	{
		cmd[0] = ' ';
		if (cmd[1] != '\0' && cmd[1] == '>')
		{
			*rp = '+';
			cmd[1] = ' ';
			rtn = ft_getword(cmd, out);
		}
		else
		{
			*rp = 'w';
			rtn = ft_getword(cmd, out);
		}
	}
	return (rtn);
}
