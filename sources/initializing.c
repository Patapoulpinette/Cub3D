/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/04 18:25:45 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_values(t_structs *structs)
{
	int		i = 0;
	char	**map = calloc(20, sizeof(char *));

	map[i++] = ft_strdup("11111111111111111111111111111");
	map[i++] = ft_strdup("10010000000000000000000000001");
	map[i++] = ft_strdup("10010000000000000000000000001");
	map[i++] = ft_strdup("10010000000000000000001111001");
	map[i++] = ft_strdup("10010000000000000000001001001");
	map[i++] = ft_strdup("10000000000000000000001000001");
	map[i++] = ft_strdup("10000000000000011111111111111");
	map[i++] = ft_strdup("1000000101000001");
	map[i++] = ft_strdup("1000000010000001");
	map[i++] = ft_strdup("10000001010000011111");
	map[i++] = ft_strdup("10000000000000000001");
	map[i++] = ft_strdup("10000000000000000001");
	map[i++] = ft_strdup("10000000000000000001");
	map[i++] = ft_strdup("11111111111111111111");

	structs->ray->tile_size = 64;
	structs->ray->wall_height = 64;
	structs->ray->angle60 = SCREEN_WIDTH;
	structs->ray->angle30 = floor(structs->ray->angle60 / 2);
	structs->ray->angle15 = floor(structs->ray->angle30 / 2);
	structs->ray->angle90 = floor(structs->ray->angle30 * 3);
	structs->ray->angle180 = floor(structs->ray->angle90 * 2);
	structs->ray->angle270 = floor(structs->ray->angle90 * 3);
	structs->ray->angle360 = floor(structs->ray->angle60 * 6);
	structs->ray->angle0 = 0;
	structs->ray->angle5 = floor(structs->ray->angle30 / 6);
	structs->ray->angle10 = floor(structs->ray->angle5 * 2);
	structs->ray->angle45 = floor(structs->ray->angle15 * 3);
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

	structs->player->x = 42;
	structs->player->y = 22;
	structs->player->angle = structs->ray->angle5 + structs->ray->angle5;
	structs->player->dist_from_proj_plane = 277;
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
		radian = degtorad((double) i, structs->ray) + 0.0001;
		structs->ray->sin_table[i] = sin(radian);
		structs->ray->sin_table_inv[i] = 1 / structs->ray->sin_table[i];
		structs->ray->cos_table[i] = cos(radian);
		structs->ray->cos_table_inv[i] = 1 / structs->ray->cos_table[i];
		structs->ray->tan_table[i] = tan(radian);
		structs->ray->tan_table_inv[i] = 1 / structs->ray->tan_table[i];
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
	dprintf(2, "len max ligne : %d\n", result);
	return (result);
}
