/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/22 16:35:44 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	draw_map2d(structs->image, structs->minimap);
	raycasting_algo(structs->image, structs->raycasting, structs->player, structs->minimap);
	draw_rays2d(structs->image, structs->minimap, structs->player);
	draw_player(structs->image, structs->player);
	mlx_put_image_to_window(structs->mlx->mlx, structs->mlx->window, structs->image->img, 0, 0);
}

void	clear_image(t_image *image)
{
	int	i;
	int	j;

	i = 0;
	while (i <= SCREEN_WIDTH)
	{
		j = 0;
		while (j <= SCREEN_HEIGHT)
		{
			my_img_pixel_put(image, i, j, 0x000000);
			j++;
		}
		i++;
	}
}

void	draw_player(t_image *image, t_player *player)
{
	t_points	points;

	my_img_pixel_put(image, player->px, player->py, PINK);
	my_img_pixel_put(image, player->px - 1, player->py - 1, PINK);
	my_img_pixel_put(image, player->px, player->py - 1, PINK);
	my_img_pixel_put(image, player->px + 1, player->py - 1, PINK);
	my_img_pixel_put(image, player->px + 1, player->py, PINK);
	my_img_pixel_put(image, player->px + 1, player->py + 1, PINK);
	my_img_pixel_put(image, player->px, player->py + 1, PINK);
	my_img_pixel_put(image, player->px - 1, player->py + 1, PINK);
	my_img_pixel_put(image, player->px - 1, player->py, PINK);
	points.x0 = player->px;
	points.y0 = player->py;
	points.x1 = player->px + player->pdx * 3;
	points.y1 = player->py + player->pdy * 3;
	bhm_line(image, &points, PINK);
}

void	draw_rays2d(t_image *image, t_minimap *minimap, t_player *player)
{
	t_points	pt;

	(void) minimap;
	pt.x0 = player->px;
	pt.y0 = player->py;
	pt.x1 = player->px + player->pdx * 30;
	pt.y1 = player->py + player->pdy * 30;
	bhm_line(image, &pt, YELLOW);
}

void	draw_map2d(t_image *image, t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->map_ylen)
	{
		x = 0;
		while (x < minimap->map_xlen)
		{
			if (!ft_strncmp(&minimap->map[y][x], "1", 1))
				draw_walls2d(image, minimap, x, y);
			x++;
		}
		y++;
	}
}

void	draw_walls2d(t_image *image, t_minimap *minimap, int x, int y)
{
	int	big_x;
	int	big_y;
	int	zoom;

	zoom = 150 / minimap->map_xlen;
	big_y = y * zoom;
	while (big_y <= (y * zoom + zoom - 1))
	{
		big_x = x * zoom;
		while (big_x <= (x * zoom + zoom - 1))
		{
			my_img_pixel_put(image, big_x, big_y, 0xFFFFFF);
			big_x++;
		}
		big_y++;
	}
}

void	my_img_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= image->x_img || y >= image->y_img)
		return ;
	dst = image->addr + (y * image->size_line + x
			* (image->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}
