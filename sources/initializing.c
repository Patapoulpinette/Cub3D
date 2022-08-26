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

void	initialize_values(t_algo_params *algo_params)
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

	algo_params->render_delay = 30;
	algo_params->player_FOV = 60;
	algo_params->player_half_FOV = algo_params->player_FOV / 2;
	algo_params->player_X = 2; //à enlever à terme car viendra de la map parsée
	algo_params->player_Y = 2; //à enlever à terme car viendra de la map parsée
	algo_params->player_angle = 90; //à enlever à terme car viendra de la map parsée
	algo_params->rayCasting_increment_angle = algo_params->player_FOV / SCREEN_WIDTH;
	algo_params->rayCasting_precision = 64;
	algo_params->map = mappy;
}
