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

void	initialize_values(t_raycasting *raycasting)
{
	char	*mappy[] = {
			"1111111111",
			"1000000001",
			"1000000001",
			"1001101001",
			"1001001001",
			"1001001001",
			"1001011001",
			"1000000001",
			"1000000001",
			"1111111111",
	}; //à enlever à terme car viendra de la map parsée

	raycasting->render_delay = 30;
	raycasting->player_FOV = 60;
	raycasting->player_half_FOV = raycasting->player_FOV / 2;
	raycasting->player_X = 2; //à enlever à terme car viendra de la map parsée
	raycasting->player_Y = 2; //à enlever à terme car viendra de la map parsée
	raycasting->player_angle = 90; //à enlever à terme car viendra de la map parsée
	raycasting->increment_angle = raycasting->player_FOV / SCREEN_WIDTH;
	raycasting->rayCasting_precision = 64;
	raycasting->map = mappy;
}
