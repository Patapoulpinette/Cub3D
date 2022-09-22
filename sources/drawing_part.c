/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/22 13:56:24 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	draw_map2d(structs->image, structs->minimap);
	draw_player(structs->image, structs->player);
//	draw_rays2d(structs->image, structs->minimap, structs->player);
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
	float		a_tan;
	t_points	pt;

	minimap->rangle = player->pangle;
	minimap->ray = 0;
	while (minimap->ray < 1)
	{
		//Check horizontal lines
		minimap->dof = 0;
		a_tan = -1 / tan(minimap->rangle);
		if (minimap->rangle > M_PI) //looking up
		{
			minimap->ry = (((int)player->py >> 6) << 6) - 0.0001;
			minimap->rx = (player->py - minimap->ry) * a_tan + player->px;
			minimap->yo = -64;
			minimap->xo = -minimap->yo * a_tan;
		}
		if (minimap->rangle < M_PI) //looking down
		{
			minimap->ry = (((int)player->py >> 6) << 6) + 64;
			minimap->rx = (player->py - minimap->ry) * a_tan + player->px;
			minimap->yo = 64;
			minimap->xo = -minimap->yo * a_tan;
		}
		if (minimap->rangle == 0 || minimap->rangle == M_PI) //looking straight left or right
		{
			minimap->rx = player->px;
			minimap->ry = player->py;
			minimap->dof = 8;
		}
		while (minimap->dof < 8)
		{
			minimap->mx = (int) (minimap->rx) >> 6;
			minimap->my = (int) (minimap->ry) >> 6;
			minimap->mp = minimap->my * minimap->map_xlen + minimap->mx;
			if (minimap->mp < minimap->map_xlen * minimap->map_ylen && minimap->map[minimap->my * minimap->map_xlen][minimap->mx] == '1') //hit wall
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

int	calculate_map_len_max(t_minimap *minimap)
{
	int	result;
	int	j;

	result = 0;
	j = 0;
	while (minimap->map[j])
	{
		if ((int)ft_strlen(minimap->map[j]) > result)
			result = ft_strlen(minimap->map[j]);
		j++;
	}
	dprintf(2, "len max ligne : %d\n", result);
	return (result);
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
