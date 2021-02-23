/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 06:19:50 by joopark           #+#    #+#             */
/*   Updated: 2020/10/09 15:26:34 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_lstsize(t_list *lst)
{
	t_list	*tmp;
	int		rtn;

	rtn = 0;
	tmp = lst;
	while (tmp != NULL)
	{
		tmp = tmp->next;
		rtn++;
	}
	return (rtn);
}
