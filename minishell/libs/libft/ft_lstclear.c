/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 07:18:45 by joopark           #+#    #+#             */
/*   Updated: 2020/10/11 15:35:12 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (lst != NULL && *lst != NULL)
	{
		while (*lst != NULL)
		{
			del((*lst)->content);
			tmp = (*lst);
			(*lst) = (*lst)->next;
			free(tmp);
		}
	}
}
