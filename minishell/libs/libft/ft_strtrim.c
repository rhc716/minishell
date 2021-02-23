/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:52:44 by joopark           #+#    #+#             */
/*   Updated: 2020/10/07 22:03:15 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_charsearch(char c, char const *chars)
{
	while (*chars)
	{
		if (*chars == c)
			return (1);
		chars++;
	}
	return (0);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		k;
	char	*rtn;

	if (s1 == ((char *)0) || set == ((char *)0))
		return (((char *)0));
	j = ft_strlen((char *)s1) - 1;
	i = 0;
	while (j >= 0 && ft_charsearch(s1[j], set) == 1)
		j--;
	while (i <= j && ft_charsearch(s1[i], set) == 1)
		i++;
	if (!(rtn = (char *)malloc(sizeof(char) * (j - i + 2))))
		return ((char *)0);
	k = 0;
	while (i <= j)
	{
		rtn[k++] = s1[i];
		i++;
	}
	rtn[k] = '\0';
	return (rtn);
}
