/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 20:43:54 by joopark           #+#    #+#             */
/*   Updated: 2020/10/11 17:33:19 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(
	char *restrict dst, const char *restrict src, size_t dstsize)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen((char *)dst);
	while ((dstsize > i + len + 1) && (src[i] != '\0'))
	{
		dst[i + len] = src[i];
		i++;
	}
	if (dstsize > len)
		dst[i + len] = '\0';
	if (dstsize > len)
		return (ft_strlen((char *)src) + len);
	else
		return (ft_strlen((char *)src) + dstsize);
}
