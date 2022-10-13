/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/13 16:08:05 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_values(t_structs *structs)
{
	int		i = 0;
	char	**map = calloc(20, sizeof(char *));

	map[i++] = ft_strdup("1111111111111111111111111111");
	map[i++] = ft_strdup("1000000000000100000000000001");
	map[i++] = ft_strdup("1000000000000100000000000001");
	map[i++] = ft_strdup("1001111111100100000010000001");
	map[i++] = ft_strdup("1001000000000000000000000001");
	map[i++] = ft_strdup("1001000000000000000000000001");
	map[i++] = ft_strdup("1111000000011111111000001111");
	map[i++] = ft_strdup("100000000001      1000001");
	map[i++] = ft_strdup("100000000001      1000001");
	map[i++] = ft_strdup("1000000000011111111000111");
	map[i++] = ft_strdup("10000000000000000000001");
	map[i++] = ft_strdup("10000000000000000000001");
	map[i++] = ft_strdup("10000000000100000000001");
	map[i++] = ft_strdup("11111111111111111111111");

	structs->ray->tile_size = 64;
	structs->ray->wall_height = 64;
	structs->ray->angle60 = SCREEN_WIDTH;
	structs->ray->angle30 = structs->ray->angle60 / 2;
	structs->ray->angle15 = structs->ray->angle30 / 2;
	structs->ray->angle90 = structs->ray->angle30 * 3;
	structs->ray->angle180 = structs->ray->angle90 * 2;
	structs->ray->angle270 = structs->ray->angle90 * 3;
	structs->ray->angle360 = structs->ray->angle60 * 6;
	structs->ray->angle0 = 0;
	structs->ray->angle5 = structs->ray->angle30 / 6;
	structs->ray->angle10 = structs->ray->angle5 * 2;
	structs->ray->angle45 = structs->ray->angle15 * 3;
	structs->ray->sin_table = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->sin_table_inv = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->cos_table = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->cos_table_inv = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->tan_table = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->tan_table_inv = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->fish_table = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->step_x_table = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->step_y_table = ft_calloc(structs->ray->angle360 + 1, sizeof(double));
	structs->ray->proj_plane_y_center = SCREEN_HEIGHT / 2;
	fill_tables(structs);
	init_tables(structs->ray);

	structs->player->x = 360;
	structs->player->y = 460;
	structs->player->angle = structs->ray->angle90; //facing down
	structs->player->x_dir = structs->ray->cos_table[structs->player->angle]; //facing down ~ 0
	structs->player->y_dir = structs->ray->sin_table[structs->player->angle]; //facing down ~ 1
	structs->player->dist_from_proj_plane = (SCREEN_WIDTH / 2) / tan(deg_to_rad(30));
	structs->player->height = 32; // because size of wall is 64
	structs->player->speed = 16;

	structs->minimap->map = map;
	structs->minimap->map_xlen = calculate_map_len_max(structs->minimap);
	structs->minimap->map_ylen = ft_tablen(map);
	structs->minimap->wall_size = 150 / structs->minimap->map_xlen;
}

void	fill_tables(t_structs *structs)
{
	int		i;
	double	radian;

	i = 0;
	while (i <= structs->ray->angle360)
	{
		radian = degtorad((double) i, structs->ray)+ 0.000001;
		structs->ray->sin_table[i] = sin(radian);
		structs->ray->sin_table_inv[i] = 1 / structs->ray->sin_table[i];
		structs->ray->cos_table[i] = cos(radian);
		structs->ray->cos_table_inv[i] = 1 / structs->ray->cos_table[i];
		structs->ray->tan_table[i] = tan(radian);
		structs->ray->tan_table_inv[i] = 1 / structs->ray->tan_table[i];
		i++;
	}
}

void	init_tables(t_raycasting *ray)
{
	int		i;
	double	radian;

	i = 0;
	while (i <= ray->angle360)
	{
		//facing left
		if (i >= ray->angle90 && i < ray->angle270)
		{
			ray->step_x_table[i] = ray->tile_size / ray->tan_table[i];
			if (ray->step_x_table[i] > 0)
				ray->step_x_table[i] = -ray->step_x_table[i];
		}
		//facing right
		else
		{
			ray->step_x_table[i] = ray->tile_size / ray->tan_table[i];
			if (ray->step_x_table[i] < 0)
				ray->step_x_table[i] = -ray->step_x_table[i];
		}

		//facing down
		if (i >= ray->angle0 && i < ray->angle180)
		{
			ray->step_y_table[i] = ray->tile_size * ray->tan_table[i];
			if (ray->step_y_table[i] < 0)
				ray->step_y_table[i] = -ray->step_y_table[i];
		}
		//facing up
		else
		{
			ray->step_y_table[i] = ray->tile_size * ray->tan_table[i];
			if (ray->step_y_table[i] > 0)
				ray->step_y_table[i] = -ray->step_y_table[i];
		}
		i++;
	}
	
	//create table for fixing fishbowl distortion view
	i = -ray->angle30;
	while (i <= ray->angle30)
	{
		radian = degtorad((double) i, ray);
		ray->fish_table[i + (int) ray->angle30] = 1 / cos(radian);
		i++;
	}
}

int	calculate_map_len_max(t_minimap *minimap)
{
	int	result;
	int	j;

	result = 0;
	j = 0;
	while (minimap->map[j])
	{
		if ((int)ft_strlen(minimap->map[j]) > result)
			result = ft_strlen(minimap->map[j]);
		j++;
	}
	return (result);
}

double	deg_to_rad(double angle)
{
	return (angle * M_PI / 180);
}
