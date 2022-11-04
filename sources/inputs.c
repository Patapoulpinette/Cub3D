/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:17:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/04 18:19:06 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	press_key(int key, t_structs *structs)
{
	if (key == ESC)
	{
		mlx_destroy_image(structs->mlx->mlx, structs->image->img);
		mlx_destroy_window(structs->mlx->mlx, structs->mlx->window);
		free(structs->mlx->mlx);
		free_tab_c(structs->ray->map);
		exit(EXIT_SUCCESS);
	}
	else if (key == LEFT_ARROW)
		rotate_camera_left(structs, structs->ray->rot_speed);
	else if (key == RIGHT_ARROW)
		rotate_camera_right(structs, structs->ray->rot_speed);
	else if (key == W || key == S || key == UP_ARROW || key == DOWN_ARROW)
		move_player(key, structs);
	else if (key == A || key == D)
		translate_player(key, structs);
	else if (key == PLUS)
		structs->minimap->wall_zoom += 1;
	else if (key == MINUS)
		structs->minimap->wall_zoom -= 1;
	else
		dprintf(2, "key number : %d\n", key);
	draw_in_image(structs);
	return (0);
}

int	press_mouse(int key, int x, int y, t_structs *structs)
{
	if (key == 1 | key == 2)
	{
		structs->mouse->save_x = x;
		structs->mouse->save_y = y;
		structs->mouse->button_press = key;
		mlx_mouse_hide();
	}
	return (0);
}

int	release_mouse(int key, int x, int y, t_structs *structs)
{
	(void) key;
	(void) x;
	(void) y;
	structs->mouse->button_press = 0;
	mlx_mouse_move(structs->mlx->window, structs->mouse->save_x,
		structs->mouse->save_y);
	mlx_mouse_show();
	return (0);
}

int	move_mouse(int x, int y, t_structs *structs)
{
	(void) y;
	if (structs->mouse->button_press)
	{
		if ((x - structs->mouse->prev_mouse_x) < 0)
			rotate_camera_left(structs, 0.06);
		else if ((x - structs->mouse->prev_mouse_x) > 0)
			rotate_camera_right(structs, 0.06);
		draw_in_image(structs);
		structs->mouse->prev_mouse_x = x;
	}
	return (0);
}

int	exit_program(t_structs *structs)
{
	mlx_destroy_image(structs->mlx->mlx, structs->image->img);
	mlx_destroy_window(structs->mlx->mlx, structs->mlx->window);
	free(structs->mlx->mlx);
	free_tab_c(structs->ray->map);
	exit(EXIT_SUCCESS);
}
