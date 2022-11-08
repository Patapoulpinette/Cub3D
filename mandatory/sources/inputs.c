/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:17:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 16:09:40 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_key(int key, t_structs *structs)
{
	if (key == ESC)
		exit_program(structs);
	else if (key == LEFT_ARROW)
		rotate_camera_left(structs, structs->ray->rot_speed);
	else if (key == RIGHT_ARROW)
		rotate_camera_right(structs, structs->ray->rot_speed);
	else if (key == W || key == S || key == UP_ARROW || key == DOWN_ARROW)
		move_player(key, structs);
	else if (key == A || key == D)
		translate_player(key, structs);
	draw_in_image(structs);
	return (0);
}

int	exit_program(t_structs *structs)
{
	mlx_destroy_image(structs->mlx->mlx, structs->image->img);
	mlx_destroy_window(structs->mlx->mlx, structs->mlx->window);
	free_tab_c(structs->data->game_map);
	free_tab_c(structs->data->f_game_map);
	free(structs->data->no_path);
	free(structs->data->so_path);
	free(structs->data->we_path);
	free(structs->data->ea_path);
	free(structs->texture);
	exit(EXIT_SUCCESS);
}
