/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/06 21:47:13 by joopark           #+#    #+#             */
/*   Updated: 2020/10/11 15:04:02 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	s_p;
	size_t	f_p;

	s_p = 0;
	f_p = 0;
	while (haystack[s_p] != '\0' && len > 0)
	{
		if (haystack[s_p] == needle[f_p])
			f_p++;
		else
		{
			if (needle[f_p] == '\0')
				return ((char *)&haystack[s_p - f_p]);
			else
				f_p = (haystack[s_p] == needle[0]) ? 1 : 0;
		}
		s_p++;
		len--;
	}
	return ((needle[f_p] == '\0') ? ((char *)&haystack[s_p - f_p]) : (void*)0);
}
