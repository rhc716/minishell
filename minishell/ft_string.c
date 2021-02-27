/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:50:25 by joopark           #+#    #+#             */
/*   Updated: 2021/02/27 01:57:27 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 문자열 합치는 함수
char				*ft_strnstack(char *stack, char *str, size_t n)
{
	char			*rtn;
	size_t			len;

	if (stack == NULL)
	{
		if (!(stack = (char *)malloc(sizeof(char) * 1)))
			return (NULL);
		stack[0] = '\0';
	}
	len = ft_strlen(stack);
	if (!(rtn = (char *)malloc(sizeof(char) * (len + ft_strlen(str) + 1))))
	{
		if (stack)
			free(stack);
		return (NULL);
	}
	ft_strlcpy(rtn, stack, len + 1);
	ft_strlcpy(rtn + len, str, n + 1);
	free(stack);
	rtn[len + n] = '\0';
	return (rtn);
}

// 2차원 문자열 배열을 복제하는 함수
char			**ft_strsdup(char *str[])
{
	char		**rtn;
	int			i;

	i = 0;
	while (str[i] != NULL)
		i++;
	rtn = malloc(sizeof(char *) * (i + 1));
	if (rtn == NULL)
		return (NULL);
	while (i >= 0)
	{
		if (str[i] != NULL)
			rtn[i] = ft_strdup(str[i]);
		else
			rtn[i] = NULL;
		i--;
	}
	return (rtn);
}

// 2차원 문자열 배열을 메모리 할당 해제하는 함수
void			ft_strsfree(char *str[])
{
	int			i;

	i = 0;
	while (str[i] != NULL)
		i++;
	while (i >= 0)
	{
		if (str[i] != NULL)
			free(str[i]);
		i--;
	}
	free(str);
}

// (리다이렉트 전용) str에서 단어 하나만 가져옴. 공백 포함 단어 길이만큼 리턴. 단어는 공백으로 비움.
int				ft_getword(char *str, char **word)
{
	int			rtn;
	int			start;
	char		*tmp;

	rtn = 0;
	while (str[rtn] != '\0' && str[rtn] == ' ')
		rtn++;
	start = rtn;
	while (str[rtn] != '\0' && str[rtn] != ' ')
		rtn++;
	if (*word != NULL)
		free(*word);
	tmp = ft_substr(str, start, rtn - start);
	tmp = ft_parse_replace_inquote(tmp, (char)0xff, ' ');
	*word = ft_strtrim(tmp, "\'\"");
	while (start != rtn)
	{
		str[start] = ' ';
		start++;
	}
	return (rtn);
}
