/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 00:08:50 by joopark           #+#    #+#             */
/*   Updated: 2021/02/24 15:04:22 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 명령어 (명령어 + 인수들)를 공백 단위로 파싱하여 2차원 배열로 리턴. quote 내의 0xff는 공백으로 다시 치환
char			**ft_parse_exec(char *cmd)
{
	char		**rtn;
	int			i;
	int			j;
	
	i = 0;
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

// 명령어 (명령어 + 인수들)의 quote를 제거함. quote 내의 공백은 0xff로 치환한다.
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
