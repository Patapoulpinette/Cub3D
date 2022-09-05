/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/05 11:34:50 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting_values(t_raycasting *raycasting)
{
	raycasting->player_x = 22;//posX
	raycasting->player_y = 12;//posY
	raycasting->direction_x = -1;//dirX
	raycasting->direction_y = 0;//dirY
	raycasting->camera_plane_x = 0;//planeX
	raycasting->camera_plane_y = 0.66;//planeY
	raycasting->frame_time = 0;//time
	raycasting->old_frame_time = 0;//oldTime
}
