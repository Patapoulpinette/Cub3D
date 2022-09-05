/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/25 10:58:07 by dbouron           #+#    #+#             */
/*   Updated: 2022/08/25 11:36:33 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_raycasting_values(t_raycasting *raycasting)
{
	raycasting->player_x = 22;
	raycasting->player_y = 12;
	raycasting->direction_x = -1;
	raycasting->direction_y = 0;
	raycasting->camera_x = 0;
	raycasting->camera_y = 0.66;
	raycasting->frame_time = 0;
	raycasting->old_frame_time = 0;
}
