/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:03:34 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/29 14:55:50 by dbouron          ###   ########lyon.fr   */
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

int	press_key(int key, t_structs *structs)
{
	if (key == 53) //ESC
	{
		mlx_destroy_image(structs->mlx->mlx, structs->image->img);
		mlx_destroy_window(structs->mlx->mlx, structs->mlx->window);
		free(structs->mlx->mlx);
		free_tab_c(structs->minimap->map);
		exit(EXIT_SUCCESS);
	}
	else if (key == 123 || key == 124)
		rotate_camera(key, structs);//fleche gauche/droite pour tourner camera
	else if (key == 13 || key == 1)
		move_player(key, structs);//WS pour faire avancer/reculer le personnage
	else if (key == 0 || key == 2)
		translate_player(key, structs);//AD pour faire translater le personnage
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
	free_tab_c(structs->minimap->map);
	exit(EXIT_SUCCESS);
}

void	display_window(void)
{
	t_mlx			mlx;
	t_image			image;
	t_player		player;
	t_minimap		minimap;
	t_raycasting	raycasting;
	t_structs		structs;

	structs.mlx = &mlx;
	structs.image = &image;
	structs.player = &player;
	structs.minimap = &minimap;
	structs.ray = &raycasting;
	mlx.x_win = SCREEN_WIDTH;
	mlx.y_win = SCREEN_HEIGHT;
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, mlx.x_win, mlx.y_win, "Cub3D");
	init_values(&structs);
	create_image(&mlx, &image);
	draw_in_image(&structs);
	//mlx_do_key_autorepeaton(mlx.mlx);
	//mlx_key_hook(mlx.window, press_key, &structs);
	mlx_hook(mlx.window, 02, 0L, press_key, &structs);
	mlx_hook(mlx.window, 17, 1L << 5, exit_program, &structs);
	mlx_loop(mlx.mlx);
}
