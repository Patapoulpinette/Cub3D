/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/22 13:59:39 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_values(t_structs *structs)
{
	int		i = 0;
	char	**map = calloc(20, sizeof(char *));

	map[i++] = ft_strdup("1111111111111111");
	map[i++] = ft_strdup("1010000000000001");
	map[i++] = ft_strdup("1010000001111001");
	map[i++] = ft_strdup("1010000001000001");
	map[i++] = ft_strdup("1000000001110001");
	map[i++] = ft_strdup("1000010000011111");
	map[i++] = ft_strdup("100000000001");
	map[i++] = ft_strdup("100010000011");
	map[i++] = ft_strdup("10000000001");
	map[i++] = ft_strdup("10000000001");
	map[i++] = ft_strdup("11111111111");

	structs->player->px = 42;
	structs->player->py = 22;
	structs->player->pangle = 3 * M_PI / 2;
	structs->player->pdx = cos(structs->player->pangle) * 5;
	structs->player->pdy = sin(structs->player->pangle) * 5;

	structs->minimap->map = map;
	structs->minimap->map_xlen = calculate_map_len_max(structs->minimap);
	structs->minimap->map_ylen = ft_tablen(map);
}
