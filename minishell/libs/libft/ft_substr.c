/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 07:48:28 by joopark           #+#    #+#             */
/*   Updated: 2020/10/05 17:09:52 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*rtn;
	size_t	cnt;

	cnt = 0;
	if (s == ((char *)0))
		return ((char *)0);
	if (!(rtn = (char *)malloc(sizeof(char) * (len + 1))))
		return ((char *)0);
	if (ft_strlen((char *)s) <= start)
	{
		rtn[cnt] = '\0';
		return (rtn);
	}
	while (cnt < len)
	{
		rtn[cnt] = s[cnt + start];
		cnt++;
	}
	rtn[cnt] = '\0';
	return (rtn);
}
