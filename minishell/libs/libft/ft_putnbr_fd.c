/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/08 17:13:16 by joopark           #+#    #+#             */
/*   Updated: 2020/10/09 02:20:00 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr_fd(int n, int fd)
{
	long	tmp;
	long	base;
	char	c;

	tmp = n >= 0 ? (long)n : -1L * n;
	base = 1L;
	while ((base *= 10) < tmp)
		;
	if (n < 0)
		write(fd, "-", 1);
	while (base /= 10)
	{
		c = (tmp / base) + '0';
		write(fd, &c, 1);
		tmp = tmp % base;
	}
}
