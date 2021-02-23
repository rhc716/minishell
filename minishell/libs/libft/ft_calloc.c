/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 22:32:41 by joopark           #+#    #+#             */
/*   Updated: 2020/10/06 22:32:42 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_calloc(size_t count, size_t size)
{
	void	*rtn;
	size_t	i;

	i = 0;
	if (!(rtn = malloc(count * size)))
		return ((void *)0);
	while (i < (count * size))
	{
		((unsigned char *)rtn)[i] = 0;
		i++;
	}
	return (rtn);
}
