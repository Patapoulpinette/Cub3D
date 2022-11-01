/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/31 16:30:57 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting_values(t_structs *structs)
{
	structs->ray->map = structs->data->f_game_map;

	structs->texture[north].path = structs->data->no_path;
	structs->texture[east].path = structs->data->ea_path;
	structs->texture[south].path = structs->data->so_path;
	structs->texture[west].path = structs->data->we_path;

	structs->player->x = 10;
	structs->player->y = 7;
	structs->player->dir_x = -1;
	structs->player->dir_y = 0;

	structs->ray->plane_x = 0;
	structs->ray->plane_y = 0.66;
	structs->ray->move_speed = 0.3;
	structs->ray->rot_speed = 0.1;

	structs->minimap->map_xlen = calculate_map_len_max(structs->ray);
	structs->minimap->map_ylen = ft_tablen(structs->ray->map);
	structs->minimap->wall_zoom = 150 / structs->minimap->map_xlen;
}

int	calculate_map_len_max(t_raycasting *ray)
{
	int	result;
	int	j;

	result = 0;
	j = 0;
	while (ray->map[j])
	{
		if ((int)ft_strlen(ray->map[j]) > result)
			result = ft_strlen(ray->map[j]);
		j++;
	}
	return (result);
}
