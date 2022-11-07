/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/07 10:37:13 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	raycasting_algo(structs);
	draw_map2d(structs->image, structs->ray, structs->minimap);
	draw_map2d_player(structs->image, structs->player, structs->minimap);
	mlx_put_image_to_window(structs->mlx->mlx, structs->mlx->window, \
		structs->image->img, 0, 0);
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
					minimap->wall_zoom, BLACK);
			c++;
		}
		r++;
	}
}

void	draw_map2d_rays(t_structs *structs, int x, int y)
{
	t_points	pt;

	pt.x0 = structs->player->y * structs->minimap->wall_zoom;
	pt.y0 = structs->player->x * structs->minimap->wall_zoom;
	pt.x1 = y * structs->minimap->wall_zoom;
	pt.y1 = x * structs->minimap->wall_zoom;
	bhm_line(structs->image, &pt, YELLOW);
}

void	draw_map2d_player(t_image *image, t_player *player, t_minimap *minimap)
{
	t_points	pt;

	my_img_pixel_put(image, player->y * minimap->wall_zoom, player->x \
		* minimap->wall_zoom, PINK);
	pt.x0 = player->y * minimap->wall_zoom;
	pt.y0 = player->x * minimap->wall_zoom;
	pt.x1 = player->y * minimap->wall_zoom + player->dir_y * 10;
	pt.y1 = player->x * minimap->wall_zoom + player->dir_x * 10;
	bhm_line(image, &pt, PINK);
	draw_fill_rect(image, player->y * minimap->wall_zoom - 1, player->x \
		* minimap->wall_zoom - 1, 3, 3, PINK);
}
