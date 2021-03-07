/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joopark <joopark@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/02 18:27:32 by joopark           #+#    #+#             */
/*   Updated: 2021/03/07 14:26:01 by joopark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ft_quote_remove_list(char **str)
{
	int			i;
	int			j;
	char		**tmps;

	i = 0;
	while (str[i] != NULL)
	{
		if (ft_parse_replace_quote(str[i], (char)0xfa) == NULL)
		{
			free(str[i]);
			str[i] = ft_strdup("");
		}
		tmps = ft_split(str[i], (char)0xfa);
		j = 0;
		free(str[i]);
		str[i] = NULL;
		while (tmps[j] != NULL)
		{
			str[i] = ft_strnstack(str[i], tmps[j], ft_strlen(tmps[j]));
			j++;
		}
		ft_strsfree(tmps);
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
