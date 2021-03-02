/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:50:25 by joopark           #+#    #+#             */
/*   Updated: 2021/03/02 13:35:48 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_strjoin에 free 기능 추가
char	*ft_strjoin_free(char *s1, char *s2, int free_case)
{
	char	*re;
	size_t	s1_len;
	size_t	s2_len;

	if (!(s1) && !(s2))
		return (NULL);
	else if (!(s1) || !(s2))
		return (!(s1) ? ft_strdup(s2) : ft_strdup(s1));
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	if (!(re = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1))))
		return (NULL);
	ft_strlcpy(re, s1, s1_len + 1);
	if (free_case == 1 || free_case == 3)
		free(s1);
	ft_strlcpy(re + s1_len, s2, s2_len + 1);
	if (free_case == 2 || free_case == 3)
		free(s2);
	return (re);
}


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
