/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/17 13:08:12 by joopark           #+#    #+#             */
/*   Updated: 2021/02/25 16:29:12 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 프롬프트 출력 후 엔터 입력 전까지 문자열을 리턴 (free 필요)
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
			ft_exit("exit\n", EXIT_SUCCESS);
		rtn = ft_strnstack(rtn, line, len);
		free(line);
		if (gnl == 1)
			break;
	}
	line = ft_strnstack(ft_strdup(" "), rtn, ft_strlen(rtn)); // 파싱할 때 앞에 공백이 있어야 파싱하기 좋아 공백 추가함 (추후에 함수로 분리하는게 좋을듯)
	free(rtn);
	rtn = line;
	return (rtn);
}
