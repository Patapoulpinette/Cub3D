/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 13:46:35 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	init_raycasting_values(t_structs *structs)
{
	structs->ray->map = structs->data->f_game_map;
	structs->texture[north].path = structs->data->no_path;
	structs->texture[east].path = structs->data->ea_path;
	structs->texture[south].path = structs->data->so_path;
	structs->texture[west].path = structs->data->we_path;
	structs->player->x = structs->data->pl_x + 0.5;
	structs->player->y = structs->data->pl_y + 0.5;
	set_player_orientation_ne(structs);
	set_player_orientation_sw(structs);
	structs->ray->move_speed = 0.15;
	structs->ray->rot_speed = 0.1;
	structs->ray->ceiling_color = create_trgb(0, structs->data->ctabl[0],
			structs->data->ctabl[1], structs->data->ctabl[2]);
	structs->ray->floor_color = create_trgb(0, structs->data->ftabl[0],
			structs->data->ftabl[1], structs->data->ftabl[2]);
	structs->minimap->map_xlen = calculate_map_len_max(structs->ray->map);
	structs->minimap->map_ylen = ft_tablen(structs->ray->map);
	if (structs->minimap->map_xlen >= structs->minimap->map_ylen)
		structs->minimap->wall_zoom = 300 / structs->minimap->map_xlen;
	else
		structs->minimap->wall_zoom = 300 / structs->minimap->map_ylen;
	structs->mouse->button_press = 0;
	structs->mouse->prev_mouse_x = SCREEN_HEIGHT * 0.5;
}

void	set_player_orientation_ne(t_structs *structs)
{
	if (structs->data->pl_orientation == 'N')
	{
		structs->player->dir_x = -1;
		structs->player->dir_y = 0;
		structs->ray->plane_x = 0;
		structs->ray->plane_y = 0.66;
	}
	else if (structs->data->pl_orientation == 'E')
	{
		structs->player->dir_x = 0.000001;
		structs->player->dir_y = 1;
		structs->ray->plane_x = 0.66;
		structs->ray->plane_y = 0;
	}
}

void	set_player_orientation_sw(t_structs *structs)
{
	if (structs->data->pl_orientation == 'S')
	{
		structs->player->dir_x = 1;
		structs->player->dir_y = 0;
		structs->ray->plane_x = 0;
		structs->ray->plane_y = -0.66;
	}
	else if (structs->data->pl_orientation == 'W')
	{
		structs->player->dir_x = 0.000001;
		structs->player->dir_y = -1;
		structs->ray->plane_x = -0.66;
		structs->ray->plane_y = 0;
	}
}

int	calculate_map_len_max(char **map)
{
	int	result;
	int	j;

	result = 0;
	j = 0;
	while (map[j])
	{
		if ((int)ft_strlen(map[j]) > result)
			result = ft_strlen(map[j]);
		j++;
	}
	return (result);
}

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
