/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 22:37:13 by joopark           #+#    #+#             */
/*   Updated: 2020/10/09 02:26:08 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strdup(const char *s1)
{
	char	*rtn;
	size_t	i;

	i = ft_strlen((char *)s1);
	if (!(rtn = malloc(sizeof(char) * (i + 1))))
		return ((void *)0);
	while (1)
	{
		((unsigned char *)rtn)[i] = s1[i];
		if (i == 0)
			break ;
		i--;
	}
	return (rtn);
}
