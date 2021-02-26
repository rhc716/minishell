/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 00:08:50 by joopark           #+#    #+#             */
/*   Updated: 2021/02/26 11:50:31 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
char			*ft_parse_replace(char *cmd, char **in, char **out, char *rp)
{
	int			i;

	i = 0;
	*in = NULL;
	*out = NULL;
	while (cmd[i] != '\0')
	{
		if (ft_strncmp(&cmd[i], " < ", 3) == 0)
			i += ft_getword(&cmd[i], in);
		else if (ft_strncmp(&cmd[i], " > ", 3) == 0)
		{
			i += ft_getword(&cmd[i], out);
			*rp = 'w';
		}
		else if (ft_strncmp(&cmd[i], " >> ", 4) == 0)
		{
			i += ft_getword(&cmd[i], out);
			*rp = '+';
		}
		else
			i++;
	}
	return (cmd);
}

// 명령어 내의 리다이렉션을 찾아 해당 파일을 인수로 반환하며 리다이렉션 및 파일은 공백으로 치환한다.
char			*ft_parse_redirect(char *cmd, char **in, char **out, char *rp)
{
	int			i;

	i = 0;
	*in = NULL;
	*out = NULL;
	while (cmd[i] != '\0')
	{
		if (ft_strncmp(&cmd[i], " < ", 3) == 0)
			i += ft_getword(&cmd[i], in);
		else if (ft_strncmp(&cmd[i], " > ", 3) == 0)
		{
			i += ft_getword(&cmd[i], out);
			*rp = 'w';
		}
		else if (ft_strncmp(&cmd[i], " >> ", 4) == 0)
		{
			i += ft_getword(&cmd[i], out);
			*rp = '+';
		}
		else
			i++;
	}
	return (cmd);
}
