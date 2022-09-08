/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/07 17:39:20 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting_values(t_raycasting *raycasting)
{
	raycasting->player_x = 10;
	raycasting->player_y = 17;
	raycasting->direction_x = -1;
	raycasting->direction_y = 0;
	raycasting->camera_plane_x = 0;
	raycasting->camera_plane_y = 0.66;
	raycasting->move_speed = 0.2;
	raycasting->rot_speed = 0.1;
}
