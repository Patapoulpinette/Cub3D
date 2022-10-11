/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:56:19 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/11 17:59:53 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	f_color(t_data *data)
{
	int		i;
	int		j;
	char	*nbr;

	i = 0;
	if (data->map[data->i][data->j] == 'F')
	{
		data->j = data->j + 1;
		if (data->map[data->i][data->j] != ' ')
		{
			printf("error");
			exit(0);
		}
		while (data->map[data->i][data->j] == ' ')
			data->j++;
		data->f = 1;
		while (i < 3)
		{
			j = 0;
			data->save = data->j;
			nbr = malloc(sizeof(char) * 4);
			while (data->map[data->i][data->j] >= '0'
				&& data->map[data->i][data->j] <= '9')
				nbr[j++] = data->map[data->i][data->j++];
			if (data->j - data->save > 3 || (data->map[data->i][data->j]
				!= ',' && i != 2))
			{
				printf("error");
				exit(0);
			}
			nbr[j] = '\0';
			data->ftabl[i++] = ft_atoi(nbr);
			free(nbr);
			data->j++;
		}
		data->j--;
	}
}

void	c_color(t_data *data)
{
	int		i;
	int		j;
	char	*nbr;

	i = 0;
	if (data->map[data->i][data->j] == 'C')
	{
		data->j = data->j + 1;
		if (data->map[data->i][data->j] != ' ')
		{
			printf("error");
			exit(0);
		}
		while (data->map[data->i][data->j] == ' ')
			data->j++;
		data->c = 1;
		while (i < 3)
		{
			j = 0;
			data->save = data->j;
			nbr = malloc(sizeof(int) * 4);
			while (data->map[data->i][data->j] >= '0'
				&& data->map[data->i][data->j] <= '9')
				nbr[j++] = data->map[data->i][data->j++];
			if (data->j - data->save > 3 || (data->map[data->i][data->j]
				!= ',' && i != 2))
			{
				printf("error");
				exit(0);
			}
			nbr[j] = '\0';
			data->ctabl[i++] = ft_atoi(nbr);
			free(nbr);
			data->j++;
		}
		data->j--;
	}
}
