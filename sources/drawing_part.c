/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/13 15:46:38 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	draw_map2d(structs->image, structs->minimap);
	draw_player(structs->image, structs->player, structs->raycasting);
	draw_rays2d(structs->image, structs->minimap, structs->player);
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

void	draw_rays2d(t_image *image, t_minimap *minimap, t_player *player)
{
	float		a_tan;
	t_points	pt;

	minimap->ra = player->pa;
	minimap->ray = 0;
	while (minimap->ray < 1)
	{
		//Check horizontal lines
		minimap->dof = 0;
		a_tan = -1 / tan(minimap->ra);
		if (minimap->ra > M_PI) //looking up
		{
			minimap->ry = (((int)player->py >> 6) << 6) - 0.0001;
			minimap->rx = (player->py - minimap->ry) * a_tan + player->px;
			minimap->yo = -64;
			minimap->xo = -minimap->yo * a_tan;
		}
		if (minimap->ra < M_PI) //looking down
		{
			minimap->ry = (((int)player->py >> 6) << 6) + 64;
			minimap->rx = (player->py - minimap->ry) * a_tan + player->px;
			minimap->yo = 64;
			minimap->xo = -minimap->yo * a_tan;
		}
		if (minimap->ra == 0 || minimap->ra == M_PI) //looking straight left or right
		{
			minimap->rx = player->px;
			minimap->ry = player->py;
			minimap->dof = 8;
		}
		while (minimap->dof < 8)
		{
			minimap->mx = (int) (minimap->rx) >> 6;
			minimap->my = (int) (minimap->ry) >> 6;
			minimap->mp = minimap->my * minimap->map_x + minimap->mx;
			if (minimap->mp < minimap->map_x * minimap->map_y /* && minimap->map[minimap->my][minimap->map_x + minimap->mx] == '1' */) //revoir map[]
				minimap->dof = 8;
			else
				minimap->rx += minimap->xo;
				minimap->ry += minimap->yo;
				minimap->dof += 1;
		}
		pt.x0 = player->px;
		pt.y0 = player->py;
		pt.x1 = minimap->rx;
		pt.y1 = minimap->ry;
		bhm_line(image, &pt, 0xbde9fe);
		minimap->ray++;
	}
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
