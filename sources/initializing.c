/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/14 11:36:02 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting_values(t_raycasting *ray)
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

	ray->map = map;
	ray->player_x = 5;
	ray->player_y = 10;
	ray->dir_x = -1;
	ray->dir_y = 0;
	ray->plane_x = 0;
	ray->plane_y = 0.66;
	ray->move_speed = 0.2;
	ray->rot_speed = 0.1;
}
