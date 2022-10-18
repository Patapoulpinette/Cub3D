/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/18 17:20:25 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	raycasting_algo(structs->image, structs->player, structs->ray, structs->minimap, structs->texture);
	draw_map2d(structs->image, structs->ray, structs->minimap);
	draw_map2d_player(structs->image, structs->player, structs->minimap);
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

void	draw_map2d(t_image *image, t_raycasting *ray, t_minimap *minimap)
{
	int	r;
	int	c;

	r = 0;
	while (ray->map[r])
	{
		c = 0;
		while (ray->map[r][c])
		{
			if (ray->map[r][c] == '1')
				draw_fill_rect(image, c * minimap->wall_zoom, \
					r * minimap->wall_zoom, minimap->wall_zoom, \
					minimap->wall_zoom);
			c++;
		}
		r++;
	}
}

void	draw_map2d_rays(t_image *image, t_player *player, t_minimap *minimap, int x, int y)
{
	t_points	pt;

	pt.x0 = player->y * minimap->wall_zoom;
	pt.y0 = player->x * minimap->wall_zoom;
	pt.x1 = y * minimap->wall_zoom;
	pt.y1 = x * minimap->wall_zoom;
	bhm_line(image, &pt, YELLOW);
}

void	draw_map2d_player(t_image *image, t_player *player, t_minimap *minimap)
{
	t_points	pt;

	my_img_pixel_put(image, player->y * minimap->wall_zoom, player->x * minimap->wall_zoom, PINK);
	pt.x0 = player->y * minimap->wall_zoom;
	pt.y0 = player->x * minimap->wall_zoom;
	pt.x1 = player->y * minimap->wall_zoom + player->dir_y * 10;
	pt.y1 = player->x * minimap->wall_zoom + player->dir_x * 10;
	bhm_line(image, &pt, PINK);

	my_img_pixel_put(image, player->y * minimap->wall_zoom - 1, player->x * minimap->wall_zoom - 1, PINK);
	my_img_pixel_put(image, player->y * minimap->wall_zoom, player->x * minimap->wall_zoom - 1, PINK);
	my_img_pixel_put(image, player->y * minimap->wall_zoom + 1, player->x * minimap->wall_zoom - 1, PINK);
	my_img_pixel_put(image, player->y * minimap->wall_zoom - 1, player->x * minimap->wall_zoom, PINK);
	my_img_pixel_put(image, player->y * minimap->wall_zoom + 1, player->x * minimap->wall_zoom, PINK);
	my_img_pixel_put(image, player->y * minimap->wall_zoom - 1, player->x * minimap->wall_zoom + 1, PINK);
	my_img_pixel_put(image, player->y * minimap->wall_zoom, player->x * minimap->wall_zoom + 1, PINK);
	my_img_pixel_put(image, player->y * minimap->wall_zoom + 1, player->x * minimap->wall_zoom + 1, PINK);
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

void	draw_fill_rect(t_image *image, int x, int y, int height, int width)
{
	t_points	pt;
	int			wdth_coord;

	wdth_coord = x + width;
	while (x < wdth_coord)
	{
		pt.x0 = x;
		pt.y0 = y;
		pt.x1 = x;
		pt.y1 = y + height;
		bhm_line(image, &pt, BLACK);
		x++;
	}
}
