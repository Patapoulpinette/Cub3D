/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 06:37:05 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/11 17:58:42 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	no_path(t_data *data)
{
	if (data->map[data->i][data->j] == 'N'
		&& data->map[data->i][data->j + 1] == 'O')
	{
		data->j = data->j + 2;
		if (data->map[data->i][data->j] != ' ')
		{
			printf("error");
			exit(0);
		}
		while (data->map[data->i][data->j] == ' ')
			data->j++;
		data->no = 1;
		data->save = data->j;
		while (data->map[data->i][data->j]
			&& data->map[data->i][data->j] != ' ')
			data->j++;
		data->no_path = malloc((data->j - data->save) + 1);
		data->j = 0;
		while (data->map[data->i][data->save]
			&& data->map[data->i][data->save] != ' ')
			data->no_path[data->j++] = data->map[data->i][data->save++];
		data->no_path[data->j] = '\0';
		data->j = data->save;
	}
}

void	so_path(t_data *data)
{
	if (data->map[data->i][data->j] == 'S'
		&& data->map[data->i][data->j + 1] == 'O')
	{
		data->j = data->j + 2;
		if (data->map[data->i][data->j] != ' ')
		{
			printf("error");
			exit(0);
		}
		while (data->map[data->i][data->j] == ' ')
			data->j++;
		data->so = 1;
		data->save = data->j;
		while (data->map[data->i][data->j]
			&& data->map[data->i][data->j] != ' ')
			data->j++;
		data->so_path = malloc((data->j - data->save) + 1);
		data->j = 0;
		while (data->map[data->i][data->save]
			&& data->map[data->i][data->save] != ' ')
			data->so_path[data->j++] = data->map[data->i][data->save++];
		data->so_path[data->j] = '\0';
		data->j = data->save;
	}
}

void	we_path(t_data *data)
{
	if (data->map[data->i][data->j] == 'W'
		&& data->map[data->i][data->j + 1] == 'E')
	{
		data->j = data->j + 2;
		if (data->map[data->i][data->j] != ' ')
		{
			printf("error");
			exit(0);
		}
		while (data->map[data->i][data->j] == ' ')
			data->j++;
		data->we = 1;
		data->save = data->j;
		while (data->map[data->i][data->j]
			&& data->map[data->i][data->j] != ' ')
			data->j++;
		data->we_path = malloc((data->j - data->save) + 1);
		data->j = 0;
		while (data->map[data->i][data->save]
			&& data->map[data->i][data->save] != ' ')
			data->we_path[data->j++] = data->map[data->i][data->save++];
		data->we_path[data->j] = '\0';
		data->j = data->save;
	}
}

void	ea_path(t_data *data)
{
	if (data->map[data->i][data->j] == 'E'
		&& data->map[data->i][data->j + 1] == 'A')
	{
		data->j = data->j + 2;
		if (data->map[data->i][data->j] != ' ')
		{
			printf("error");
			exit(0);
		}
		while (data->map[data->i][data->j] == ' ')
			data->j++;
		data->ea = 1;
		data->save = data->j;
		while (data->map[data->i][data->j]
			&& data->map[data->i][data->j] != ' ')
			data->j++;
		data->ea_path = malloc((data->j - data->save) + 1);
		data->j = 0;
		while (data->map[data->i][data->save]
			&& data->map[data->i][data->save] != ' ')
			data->ea_path[data->j++] = data->map[data->i][data->save++];
		data->ea_path[data->j] = '\0';
		data->j = data->save;
	}
}
