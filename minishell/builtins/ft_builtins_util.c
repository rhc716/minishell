/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtins_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hroh <hroh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:30:51 by hroh              #+#    #+#             */
/*   Updated: 2021/03/03 17:32:25 by hroh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 2차원 char 배열을 버블소트
void	ft_sort_2d_arr(char **arr)
{
	int		i;
	int		j;
	int		k;
	char	*temp;

	i = -1;
	while (arr[++i])
	{
		j = -1;
		while (arr[++j + 1])
		{
			k = -1;
			while (arr[j][++k] && arr[j + 1][k] && arr[j][k] >= arr[j + 1][k])
			{
				if (arr[j][k] > arr[j + 1][k])
				{
					temp = arr[j + 1];
					arr[j + 1] = arr[j];
					arr[j] = temp;
					break ;
				}
			}
		}
	}
}
