/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/23 20:50:25 by joopark           #+#    #+#             */
/*   Updated: 2021/03/07 14:17:31 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char				*ft_strjoin_free(char *s1, char *s2, int free_case)
{
	char			*re;
	size_t			s1_len;
	size_t			s2_len;

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

char				**ft_strsdup(char *str[])
{
	char			**rtn;
	int				i;

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

void				ft_strsfree(char *str[])
{
	int				i;

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

int					ft_getword(char *str, char **word)
{
	int				rtn;
	int				start;
	char			*tmp;

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
	free(tmp);
	while (start != rtn)
	{
		str[start] = ' ';
		start++;
	}
	return (rtn);
}
