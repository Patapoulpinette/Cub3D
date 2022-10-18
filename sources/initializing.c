/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/18 17:35:53 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting_values(t_structs *structs)
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

	structs->ray->map = map;

	structs->texture[north].path = ft_strdup("textures/bluestone.xpm");
	structs->texture[east].path = ft_strdup("textures/colorstone.xpm");
	structs->texture[south].path = ft_strdup("textures/redbrick.xpm");
	structs->texture[west].path = ft_strdup("textures/wood.xpm");

	structs->player->x = 5;
	structs->player->y = 10;
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
