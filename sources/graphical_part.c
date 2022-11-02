/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphical_part.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 16:03:34 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/02 15:34:57 by dbouron          ###   ########lyon.fr   */
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

void	load_textures(t_mlx *mlx, t_texture *texture)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		texture[i].img = mlx_xpm_file_to_image(mlx->mlx, texture[i].path,
				&texture[i].width, &texture[i].height);
		if (!texture[i].img)
		{
			printf("Loading texture failed\n");
			exit(EXIT_FAILURE);//TODO : do a function to free all mallocs
		}
		texture[i].addr = mlx_get_data_addr(texture[i].img,
				&texture[i].bits_per_pixel, &texture[i].size_line,
				&texture[i].endian);
		if (!texture[i].addr)
		{
			printf("Loading texture failed: can't get addr of %s\n",
				texture[i].path);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	move_mouse(int x, int y, t_structs *structs)
{
	(void) y;
	if (x >= 0 && x <= (SCREEN_WIDTH * 0.25))
		rotate_camera_left(structs);
	else if (x >= (SCREEN_WIDTH * 0.75) && x <= SCREEN_WIDTH)
		rotate_camera_right(structs);
	draw_in_image(structs);
	return (0);
}

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
	else if (key == W || key == S || key == UP_ARROW || key == DOWN_ARROW)
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

void	link_structs(t_mlx *mlx, t_structs *structs)
{
	t_image			image;
	t_texture		*texture;
	t_player		player;
	t_raycasting	ray;
	t_minimap		minimap;

	structs->mlx = mlx;
	structs->image = &image;
	texture = ft_calloc(5, sizeof(t_texture));
	structs->texture = texture;
	structs->player = &player;
	structs->ray = &ray;
	structs->minimap = &minimap;
}

void	display_window(t_data *data)
{
	t_mlx		mlx;
	t_structs	structs;

	structs.data = data;
	link_structs(&mlx, &structs);
	mlx.x_win = SCREEN_WIDTH;
	mlx.y_win = SCREEN_HEIGHT;
	mlx.mlx = mlx_init();
	mlx.window = mlx_new_window(mlx.mlx, mlx.x_win, mlx.y_win, "Cub3D");
	init_raycasting_values(&structs);
	create_image(&mlx, structs.image);
	load_textures(&mlx, structs.texture);
	draw_in_image(&structs);
	mlx_hook(mlx.window, 2, 0, press_key, &structs);
	mlx_hook(mlx.window, 6, 1L << 6, move_mouse, &structs);
	mlx_hook(mlx.window, 17, 1L << 5, exit_program, &structs);
	mlx_loop(mlx.mlx);
}
