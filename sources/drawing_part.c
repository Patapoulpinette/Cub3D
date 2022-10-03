/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/03 17:45:28 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_structs *structs)
{
	clear_image(structs->image);
	draw_rays2d(structs->image, structs->minimap, structs->player, structs->ray);
	draw_map2d(structs->image, structs->minimap);
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
	points.x1 = player->px + player->dx * 3;
	points.y1 = player->py + player->dy * 3;
	bhm_line(image, &points, PINK);
}

void	draw_rays2d(t_image *image, t_minimap *minimap, t_player *player, t_raycasting *ray)
{
	t_points	pt;
	int			x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		//calculate ray position and direction
		ray->camera_x = 2 * x / (double)SCREEN_WIDTH - 1;//x coords in camera space
		ray->ray_x = player->dx + ray->plane_x * ray->camera_x;
		ray->ray_y = player->dy + ray->plane_y * ray->camera_x;

		//which box of the map we're in
		ray->map_x = (int)player->px;
		ray->map_y = (int)player->py;

		//length of ray from x or y-side to next x or y-side
		if (ray->ray_x == 0)
		{
			ray->delta_x = 1e30;
			ray->delta_y = 1e30;
		}
		else
		{
			ray->delta_x = fabs(1 / ray->ray_x);
			ray->delta_y = fabs(1 / ray->ray_y);
		}

		//calculate step and initial side_dist
		if (ray->ray_x < 0)
		{
			ray->step_x = -1;
			ray->side_x = (player->px - ray->map_x) * ray->delta_x;
		}
		else
		{
			ray->step_x = 1;
			ray->side_x = (ray->map_x + 1.0 - player->px) * ray->delta_x;
		}
		if (ray->ray_y < 0)
		{
			ray->step_y = -1;
			ray->side_y = (player->py - ray->map_y) * ray->delta_y;
		}
		else
		{
			ray->step_y = 1;
			ray->side_y = (ray->map_y + 1.0 - player->py) * ray->delta_y;
		}
		search_collisions(ray, minimap);
		draw_vertival_lines(image, ray, x);

		pt.x0 = player->px;
		pt.y0 = player->py;
		pt.x1 = ray->map_x;
		pt.y1 = ray->map_y;
		bhm_line(image, &pt, 0x70e000);

		x++;
	}
	pt.x0 = player->px;
	pt.y0 = player->py;
	pt.x1 = player->px + player->dx * 30;
	pt.y1 = player->py + player->dy * 30;
	//dprintf(2, "dx = %f | dy = %f\n", player->dx, player->dy);
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

	big_y = y * minimap->zoom;
	while (big_y <= (y * minimap->zoom + minimap->zoom - 1))
	{
		big_x = x * minimap->zoom;
		while (big_x <= (x * minimap->zoom + minimap->zoom - 1))
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
