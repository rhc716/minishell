/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:27:32 by joopark           #+#    #+#             */
/*   Updated: 2021/03/02 18:45:17 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// quote 한겹 제거
char			*ft_quote_remove(char *str)
{
	char		**split;
	int			i;

	str = ft_parse_replace_quote(str, (char)0xff);
	if (str == NULL)
		return (NULL);
	split = ft_split(str, (char)0xff);
	free(str);
	str = NULL;
	i = 0;
	while (split[i] != NULL)
	{
		str = ft_strnstack(str, split[i], ft_strlen(split[i]));
		i++;
	}
	return (str);
}

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
