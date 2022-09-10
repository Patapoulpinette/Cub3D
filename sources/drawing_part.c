/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/10 13:39:13 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	draw_map2d(structs->image, structs->minimap);
	draw_player(structs->image, structs->player, structs->raycasting);
	//raycasting_algo(structs->image, structs->raycasting);
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

void	draw_player(t_image *image, t_player *player, t_raycasting *raycasting)
{
	(void) raycasting;
	my_img_pixel_put(image, player->px + player->pdx, \
		player->py + player->pdy, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx - 1, \
		player->py + player->pdy - 1, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx, \
		player->py + player->pdy - 1, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx + 1, \
		player->py + player->pdy - 1, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx + 1, \
		player->py + player->pdy, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx + 1, \
		player->py + player->pdy + 1, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx, \
		player->py + player->pdy + 1, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx - 1, \
		player->py + player->pdy + 1, 0xbde0fe);
	my_img_pixel_put(image, player->px + player->pdx - 1, \
		player->py + player->pdy, 0xbde0fe);
}

void	draw_map2d(t_image *image, t_minimap *minimap)
{
	int	x;
	int	y;

	y = 0;
	while (y < minimap->map_y)
	{
		x = 0;
		while (x < minimap->map_x)
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

	zoom = 100 / ft_strlen(*minimap->map);
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
