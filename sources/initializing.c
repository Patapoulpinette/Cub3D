/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/22 16:25:16 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_values(t_structs *structs)
{
	int		i = 0;
	char	**map = calloc(20, sizeof(char *));

	map[i++] = ft_strdup("1111111111111111111111");
	map[i++] = ft_strdup("1010000000000000000001");
	map[i++] = ft_strdup("1010000000000001111001");
	map[i++] = ft_strdup("1010000000000001001001");
	map[i++] = ft_strdup("1000000000000001000001");
	map[i++] = ft_strdup("1000000000000001111111");
	map[i++] = ft_strdup("1000000101000001");
	map[i++] = ft_strdup("1000000010000001");
	map[i++] = ft_strdup("10000001010000011");
	map[i++] = ft_strdup("10000000000000001");
	map[i++] = ft_strdup("10000000000000001");
	map[i++] = ft_strdup("10000000000000001");
	map[i++] = ft_strdup("11111111111111111");

	structs->player->px = 42;
	structs->player->py = 22;
	structs->player->pangle = 3 * M_PI / 2;
	structs->player->pdx = cos(structs->player->pangle) * 5;
	structs->player->pdy = sin(structs->player->pangle) * 5;

	structs->minimap->map = map;
	structs->minimap->map_xlen = calculate_map_len_max(structs->minimap);
	structs->minimap->map_ylen = ft_tablen(map);

	structs->raycasting->camera_plane_x = 0;
	structs->raycasting->camera_plane_y = 0.66;
	structs->raycasting->move_speed = 0.2;
	structs->raycasting->rot_speed = 0.1;
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
