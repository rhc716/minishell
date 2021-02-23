/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/09 19:04:36 by joopark           #+#    #+#             */
/*   Updated: 2020/10/11 20:49:23 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*rtn;
	t_list	*rtntmp;

	rtn = NULL;
	while (f != NULL && lst != NULL)
	{
		if (lst != NULL)
		{
			if (!(rtntmp = ft_lstnew(f(lst->content))))
			{
				ft_lstclear(&lst, del);
				ft_lstclear(&rtn, del);
				return (NULL);
			}
			ft_lstadd_back(&rtn, rtntmp);
		}
		lst = lst->next;
	}
	return (rtn);
}
