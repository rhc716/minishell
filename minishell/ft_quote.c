/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:27:32 by joopark           #+#    #+#             */
/*   Updated: 2021/03/07 11:04:07 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ft_quote_remove_list(char **str)
{
	int			i;
	char		*tmp;

	i = 0;
	while (str[i] != NULL)
	{
		tmp = ft_strtrim(str[i], "\'\"");
		free(str[i]);
		str[i] = tmp;
		i++;
	}
	return (str);
}

char			*ft_parse_replace_quote(char *str, char c)
{
	int			i;
	char		q;

	i = 0;
	q = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (q == '\0')
			{
				q = str[i];
				str[i] = c;
			}
			else if (q == str[i])
			{
				q = '\0';
				str[i] = c;
			}
		}
		i++;
	}
	if (q != '\0')
		str = NULL;
	return (str);
}

char			*ft_parse_replace_inquote(char *str, char c, char r)
{
	int			i;
	char		q;

	i = 0;
	q = '\0';
	while (str[i] != '\0')
	{
		if (str[i] == '\'' || str[i] == '"')
		{
			if (q == '\0')
				q = str[i];
			else if (q == str[i])
				q = '\0';
		}
		else if (q != '\0' && str[i] == c)
			str[i] = r;
		i++;
	}
	return (str);
}
