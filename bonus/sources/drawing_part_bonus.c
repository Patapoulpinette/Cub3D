/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 19:38:45 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	raycasting_algo(structs);
	draw_map2d(structs->image, structs->ray, structs->minimap);
	draw_map2d_player(structs->image, structs->player, structs->minimap);
	mlx_put_image_to_window(structs->mlx->mlx, structs->mlx->window, \
		structs->image->img, 0, 0);
	structs->hud->img = mlx_xpm_file_to_image(structs->mlx->mlx, "./textures/hud.xpm", &structs->hud->width, &structs->hud->height);
	mlx_put_image_to_window(structs->mlx->mlx, structs->mlx->window, structs->hud->img, 0, SCREEN_HEIGHT - structs->hud->height);
}

void	draw_map2d(t_image *image, t_raycasting *ray, t_minimap *minimap)
{
	int				r;
	int				c;
	t_dimensions	dim;

	r = 0;
	while (ray->map[r])
	{
		c = 0;
		while (ray->map[r][c])
		{
			if (ray->map[r][c] == '1')
			{
				dim.x = c * minimap->wall_zoom;
				dim.y = r * minimap->wall_zoom;
				dim.width = minimap->wall_zoom;
				dim.height = minimap->wall_zoom;
				draw_fill_rect(image, &dim, BLACK);
			}
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
	t_points		pt;
	t_dimensions	dim;

	my_img_pixel_put(image, player->y * minimap->wall_zoom, player->x \
		* minimap->wall_zoom, PINK);
	pt.x0 = player->y * minimap->wall_zoom;
	pt.y0 = player->x * minimap->wall_zoom;
	pt.x1 = player->y * minimap->wall_zoom + player->dir_y * 10;
	pt.y1 = player->x * minimap->wall_zoom + player->dir_x * 10;
	bhm_line(image, &pt, PINK);
	dim.x = player->y * minimap->wall_zoom - 1;
	dim.y = player->x * minimap->wall_zoom - 1;
	dim.width = 3;
	dim.height = 3;
	draw_fill_rect(image, &dim, PINK);
}
