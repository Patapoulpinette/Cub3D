/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:56:19 by apercebo          #+#    #+#             */
/*   Updated: 2022/11/08 16:34:21 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_in_tab(t_data *data)
{
	while (data->inc.i < 3)
	{
		data->inc.j = 0;
		data->save = data->j;
		data->nbr = malloc(sizeof(char) * 4);
		if (!data->nbr)
			exit(EXIT_FAILURE);
		while (data->map[data->i][data->j] >= '0'
			&& data->map[data->i][data->j] <= '9')
			data->nbr[data->inc.j++] = data->map[data->i][data->j++];
		if (data->j - data->save > 3 || (data->map[data->i][data->j]
			!= ',' && data->inc.i != 2))
		{
			printf("error");
			exit(0);
		}
		data->nbr[data->inc.j] = '\0';
		data->ftabl[data->inc.i++] = ft_atoi(data->nbr);
		if (data->ftabl[data->inc.i - 1] > 255 || data->ftabl[data->inc.i - 1] < 0)
		{
			printf("ERROR IN FLOOR COLOR\n");
			color_free_exit(data);
		}
		free(data->nbr);
		data->j++;
	}
	data->j--;
}

void	f_color(t_data *data)
{
	data->inc.i = 0;
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
		data->f++;
		put_in_tab(data);
	}
}

void	put_in_tab2(t_data *data)
{
	while (data->inc.i < 3)
	{
		data->inc.j = 0;
		data->save = data->j;
		data->nbr = malloc(sizeof(int) * 4);
		if (!data->nbr)
			exit(EXIT_FAILURE);
		while (data->map[data->i][data->j] >= '0'
			&& data->map[data->i][data->j] <= '9')
			data->nbr[data->inc.j++] = data->map[data->i][data->j++];
		if (data->j - data->save > 3 || (data->map[data->i][data->j]
			!= ',' && data->inc.i != 2))
		{
			printf("error");
			exit(0);
		}
		data->nbr[data->inc.j] = '\0';
		data->ctabl[data->inc.i++] = ft_atoi(data->nbr);
		if (data->ctabl[data->inc.i - 1] > 255 || data->ctabl[data->inc.i - 1] < 0)
		{
			printf("ERROR IN ROOF COLOR\n"); //free
			color_free_exit(data);
		}
		free(data->nbr);
		data->j++;
	}
	data->j--;
}

void	c_color(t_data *data)
{
	data->inc.i = 0;
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
		data->c++;
		put_in_tab2(data);
	}
}

void	color_free_exit(t_data *data)
{
	free_tab_c(data->map);
	exit(0);
}
