/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:08:12 by joopark           #+#    #+#             */
/*   Updated: 2021/02/17 14:04:16 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*ft_getline(char **bp)
{
	int			gnl;
	size_t		len;
	char		*line;
	char		*rtn;
	
	rtn = NULL;
	while (1)
	{
		gnl = ft_get_next_line(0, &line, bp);
		len = ft_strlen(line);
		if (gnl == -1 || (gnl == 0 && len == 0 && rtn == NULL))
			exit(EXIT_FAILURE);
		rtn = ft_strnstack(rtn, line, len);
		free(line);
		if (gnl == 1)
			break;
	}
	return (rtn);
}
