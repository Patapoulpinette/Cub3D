/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:03:34 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/17 15:37:20 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_image(t_mlx *mlx, t_image *image)
{
	image->x_img = mlx->x_win;
	image->y_img = mlx->y_win;
	image->img = mlx_new_image(mlx->mlx, image->x_img, image->y_img);
	image->addr = mlx_get_data_addr(image->img, &image->bits_per_pixel,
			&image->size_line, &image->endian);
}

/* void	create_textures(t_mlx *mlx, t_texture *texture)
{
	texture->img = mlx_xpm_file_to_image(mlx->mlx, texture->path, texture->x_texture, texture->y_texture);
} */

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
		rotate_camera_left(structs);
	else if (key == RIGHT_ARROW)
		rotate_camera_right(structs);
	else if (key == W || key == S)
		move_player(key, structs);
	else if (key == A || key == D)
		translate_player(key, structs);
	else
		dprintf(2, "key number : %d\n", key);
	draw_in_image(structs);
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

void	display_window(void)
{
	t_mlx			mlx;
	t_image			image;
	t_player		player;
	t_raycasting	ray;
	t_minimap		minimap;
	t_structs		structs;

	structs.mlx = &mlx;
	structs.image = &image;
	structs.player = &player;
	structs.ray = &ray;
	structs.minimap = &minimap;
	mlx.x_win = SCREEN_WIDTH;
	mlx.y_win = SCREEN_HEIGHT;
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, mlx.x_win, mlx.y_win, "Cub3D");
	init_raycasting_values(&player, &ray, &minimap);
	create_image(&mlx, &image);
	//create_textures();
	draw_in_image(&structs);
	mlx_hook(mlx.window, 02, 0L, press_key, &structs);
	mlx_hook(mlx.window, 17, 1L << 5, exit_program, &structs);
	mlx_loop(mlx.mlx);
}
