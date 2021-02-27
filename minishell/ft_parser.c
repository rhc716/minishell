/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 00:08:50 by joopark           #+#    #+#             */
/*   Updated: 2021/02/27 01:57:23 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

// 문장 내의 한겹짜리 quote를 인수 c로 대치함. 만약 quote가 닫히지 않으면 NULL 리턴.
char			*ft_parse_replace_quote(char *str, char c)
{
	int			i;
	char		q;

	i = 0;
	q = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (q == '\0')
			{
				q = str[i];
				str[i] = c;
			}
			else if (q == str[i])
			{
				q = '\0';
				str[i] = c;
			}
		}
		i++;
	}
	if (q != '\0')
		str = NULL;
	return (str);
}

// 문장 내에서 quote로 둘러쌓인 문자 c를 r로 치환함.
char			*ft_parse_replace_inquote(char *str, char c, char r)
{
	int			i;
	char		q;

	i = 0;
	q = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (q == '\0')
				q = str[i];
			else if (q == str[i])
				q = '\0';
		}
		else if (q != '\0' && str[i] == c)
			str[i] = r;
		i++;
	}
	return (str);
}

// 문장 내에 문자 s 단위로 split 함. token 내의 c는 r로 치환
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

// 명령어 내의 리다이렉션을 찾아 해당 파일을 인수로 반환하며 리다이렉션 및 파일은 공백으로 치환한다.
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

// 리다이렉션 문자를 공백으로 채우고 파일명을 인수에 집어넣는다.
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
