/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/06 12:22:17 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	draw_rays2d(structs->image, structs->minimap, structs->player, structs->ray);
	draw_map2d(structs->image, structs->minimap, structs->player, structs->ray);
	raycast(structs->minimap, structs->player, structs->ray);
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

void	draw_rays2d(t_image *image, t_minimap *minimap, t_player *player, t_raycasting *ray)
{
	int		i;
	double	radian;

	(void) image;
	(void) minimap;
	(void) player;
	i = 0;
	while (i <= ray->angle360)
	{
		//facing left
		if (i >= ray->angle90 && i < ray->angle270)
		{
			ray->step_x_table[i] = ray->tile_size / ray->tan_table[i];
			if (ray->step_x_table[i] > 0)
				ray->step_x_table[i] = -ray->step_x_table[i];
		}
		//facing right
		else
		{
			ray->step_x_table[i] = ray->tile_size / ray->tan_table[i];
			if (ray->step_x_table[i] < 0)
				ray->step_x_table[i] = -ray->step_x_table[i];
		}

		//facing down
		if (i >= ray->angle0 && i < ray->angle180)
		{
			ray->step_y_table[i] = ray->tile_size * ray->tan_table[i];
			if (ray->step_y_table[i] < 0)
				ray->step_y_table[i] = -ray->step_y_table[i];
		}
		//facing up
		else
		{
			ray->step_y_table[i] = ray->tile_size * ray->tan_table[i];
			if (ray->step_y_table[i] > 0)
				ray->step_y_table[i] = -ray->step_y_table[i];
		}
		i++;
	}

	//create table for fixing fishbowl distortion view
	i = -ray->angle30;
	while (i <= ray->angle30)
	{
		radian = degtorad((double) i, ray);
		ray->fish_table[i + (int) ray->angle30] = 1 / cos(radian);
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
}

void	draw_ray_on_map2d(t_image *image, t_minimap *minimap, t_raycasting *ray, int x, int y)
{
	t_points	pt;

	pt.x0 = ray->map_x;
	pt.y0 = ray->map_y;
	pt.x1 = (x * minimap->wall_size) / ray->tile_size;
	pt.y1 = (y * minimap->wall_size) / ray->tile_size;
	bhm_line(image, &pt, YELLOW);
}

void	draw_player_on_map2d(t_image *image, t_player *player, t_raycasting *ray)
{
	t_points	pt;

	pt.x0 = ray->map_x;
	pt.y0 = ray->map_y;
	pt.x1 = ray->map_x + ray->cos_table[(int) player->angle] * 10;//imprécision (cast en int)
	pt.y1 = ray->map_y + ray->sin_table[(int) player->angle] * 10;//imprécision (cast en int)
	bhm_line(image, &pt, PINK);
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
