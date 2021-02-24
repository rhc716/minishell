/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:50:25 by joopark           #+#    #+#             */
/*   Updated: 2021/02/24 22:24:34 by joopark          ###   ########.fr       */
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
