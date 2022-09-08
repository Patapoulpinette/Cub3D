/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/08 12:11:32 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_player(t_image *image, t_player *player, t_raycasting *raycasting)
{
	my_img_pixel_put(image, player->px + player->pdx * 10, \
		player->py + player->pdy * 10, 0xff0000);
}

void	raycasting_algo(t_image *image, t_raycasting *raycasting)
{
	
}
