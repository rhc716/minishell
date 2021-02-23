/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 21:32:42 by joopark           #+#    #+#             */
/*   Updated: 2020/10/09 13:16:35 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*d;
	unsigned char	*s;
	long			i;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	if (d == s || len == 0)
		return (dst);
	else if (d > s && (d - s) < (long)len)
	{
		i = (long)len;
		while (i--)
			d[i] = s[i];
		return (dst);
	}
	else if (d < s && (s - d) < (long)len)
	{
		i = -1;
		while (++i < (long)len)
			d[i] = s[i];
		return (dst);
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
