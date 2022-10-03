/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/03 17:57:27 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_values(t_structs *structs)
{
	int		i = 0;
	char	**map = calloc(20, sizeof(char *));

	map[i++] = ft_strdup("11111111111111111111111111111");
	map[i++] = ft_strdup("10100000000000000000000000001");
	map[i++] = ft_strdup("10100000000000000000000000001");
	map[i++] = ft_strdup("10100000000000000000000000001");
	map[i++] = ft_strdup("10100000000000000000001111001");
	map[i++] = ft_strdup("10100000000000000000001001001");
	map[i++] = ft_strdup("10000000000000000000001000001");
	map[i++] = ft_strdup("10000000000000000000001000001");
	map[i++] = ft_strdup("10000000000000000000001000001");
	map[i++] = ft_strdup("10000000000000000000001000001");
	map[i++] = ft_strdup("10000000000000011111111111111");
	map[i++] = ft_strdup("1000000101000001");
	map[i++] = ft_strdup("1000000010000001");
	map[i++] = ft_strdup("10000001010000011111");
	map[i++] = ft_strdup("10000000000000000001");
	map[i++] = ft_strdup("10000000000000000001");
	map[i++] = ft_strdup("10000000000000000001");
	map[i++] = ft_strdup("11111111111111111111");

	structs->player->px = 42;
	structs->player->py = 22;
	structs->player->speed = 0.16;
	structs->player->angle = 3 * M_PI / 2;
	structs->player->dx = cos(structs->player->angle) * 5;
	structs->player->dy = sin(structs->player->angle) * 5;

	structs->minimap->map = map;
	structs->minimap->map_xlen = calculate_map_len_max(structs->minimap);
	structs->minimap->map_ylen = ft_tablen(map);
	structs->minimap->zoom = 150 / structs->minimap->map_xlen;

	structs->ray->plane_x = 0;
	structs->ray->plane_y = 0.66;
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
