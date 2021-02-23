/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/07 13:05:19 by joopark           #+#    #+#             */
/*   Updated: 2020/10/08 14:03:53 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_sl(char const *s, char c)
{
	int		arr_size;
	int		i;
	int		t;

	arr_size = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		t = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (t != i)
			arr_size++;
	}
	return (arr_size);
}

char		**ft_split_free(char **arr, int size)
{
	while (size--)
		free(arr[size]);
	free(arr);
	return (NULL);
}

char		**ft_split(char const *s, char c)
{
	char	**rtn;
	int		arr_size;
	int		i;
	int		t;

	if ((s == NULL)
		|| !(rtn = (char **)malloc(sizeof(char *) * (ft_sl(s, c) + 1))))
		return (NULL);
	i = 0;
	arr_size = 0;
	while (s[i] != '\0')
	{
		while (s[i] != '\0' && s[i] == c)
			i++;
		t = i;
		while (s[i] != '\0' && s[i] != c)
			i++;
		if (t != i)
			if (!(rtn[arr_size] = (char *)malloc(sizeof(char) * (i - t + 1))))
				return (ft_split_free(rtn, arr_size));
		if (t != i)
			ft_strlcpy(rtn[arr_size++], &s[t], (i - t + 1));
	}
	rtn[arr_size] = NULL;
	return (rtn);
}
