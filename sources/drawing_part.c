/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/11 14:15:54 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	raycast(structs->image, structs->minimap, structs->player, structs->ray);
	draw_map2d(structs->image, structs->minimap, structs->player, structs->ray);
	draw_player_on_map2d(structs->image, structs->player, structs->ray);
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

void	draw_map2d(t_image *image, t_minimap *minimap, t_player *player, t_raycasting *ray)
{
	int	r;
	int	c;

	r = 0;
	while (minimap->map[r])
	{
		c = 0;
		while (minimap->map[r][c])
		{
			if (minimap->map[r][c] == '1')
				draw_fill_rect(image, c * minimap->wall_size, r * minimap->wall_size, minimap->wall_size, minimap->wall_size, 0xFFFFFF);
			else
				draw_fill_rect(image, c * minimap->wall_size, r * minimap->wall_size, minimap->wall_size, minimap->wall_size, 0x000000);
			c++;
		}
		r++;
	}
	ray->map_x = player->x / ray->tile_size * minimap->wall_size;
	ray->map_y = player->y / ray->tile_size * minimap->wall_size;
	dprintf(2, "WALL_SIZE = %d\n", minimap->wall_size);
}

void	draw_ray_on_map2d(t_image *image, t_minimap *minimap, t_raycasting *ray, int x, int y)
{
	t_points	pt;

	pt.x0 = ray->map_x;
	pt.y0 = ray->map_y;
	pt.x1 = (x * minimap->wall_size) / ray->tile_size;
	pt.y1 = (y * minimap->wall_size) / ray->tile_size;
	dprintf(2, "RAYS :  x0 = %d | y0 = %d\n\tx1 = %d | y1 = %d\n\tx = %d | y = %d\n", pt.x0, pt.y0, pt.x1, pt.y1, x, y);
	bhm_line(image, &pt, YELLOW);
}

void	draw_player_on_map2d(t_image *image, t_player *player, t_raycasting *ray)
{
	t_points	pt;

	dprintf(2, "PLAYER | map_x : %d | map_y : %d | x_dir : %f | y_dir : %f\n", ray->map_x, ray->map_y, player->x_dir, player->y_dir);
	pt.x0 = ray->map_x;
	pt.y0 = ray->map_y;
	pt.x1 = ray->map_x + player->x_dir * 10;
	pt.y1 = ray->map_y + player->y_dir * 10;
	dprintf(2, "\tx0 = %d | y0 = %d | x1 = %d | y1 = %d\n", pt.x0, pt.y0, pt.x1, pt.y1);
	bhm_line(image, &pt, PINK);

	my_img_pixel_put(image, pt.x0 - 1, pt.y0 - 1, PINK);
	my_img_pixel_put(image, pt.x0, pt.y0 - 1, PINK);
	my_img_pixel_put(image, pt.x0 + 1, pt.y0 - 1, PINK);
	my_img_pixel_put(image, pt.x0 - 1, pt.y0, PINK);
	my_img_pixel_put(image, pt.x0 + 1, pt.y0, PINK);
	my_img_pixel_put(image, pt.x0 - 1, pt.y0 + 1, PINK);
	my_img_pixel_put(image, pt.x0, pt.y0 + 1, PINK);
	my_img_pixel_put(image, pt.x0 + 1, pt.y0 + 1, PINK);
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

double	degtorad(double angle, t_raycasting *ray)
{
	return ((angle * M_PI) / ray->angle180);
}

void	draw_fill_rect(t_image *image, int x, int y, int height, int width, int color)
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
		bhm_line(image, &pt, color);
		x++;
	}
}
