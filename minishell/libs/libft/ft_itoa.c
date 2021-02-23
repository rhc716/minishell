/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 05:03:27 by joopark           #+#    #+#             */
/*   Updated: 2020/10/08 14:25:59 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n)
{
	char	*rtn;
	long	tmp;
	long	base;
	int		i;

	tmp = n >= 0 ? (long)n : -1L * n;
	i = n >= 0 ? 2 : 3;
	base = 1L;
	while ((base *= 10) <= tmp)
		i++;
	if (!(rtn = (char *)malloc(sizeof(char) * i)))
		return (NULL);
	i = 0;
	if (n < 0)
		rtn[i++] = '-';
	while (base /= 10)
	{
		rtn[i++] = (tmp / base) + '0';
		tmp = tmp % base;
	}
	rtn[i] = '\0';
	return (rtn);
}
