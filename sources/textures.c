/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:52 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/31 16:32:21 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textures(t_image *image, t_player *player, t_raycasting *ray, t_texture *texture, int x)
{
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	choose_orientation(ray, texture);
	calculate_wall_x(player, ray, texture);
	calculate_x_coordinate_on_texture(ray, texture);

	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * texture[texture->orientation].height / ray->line_height;

	// Starting texture coordinate
	tex_pos = (ray->draw_start - SCREEN_HEIGHT * 0.5 + ray->line_height * 0.5) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		texture->tex_y = (int) tex_pos & (texture[texture->orientation].height - 1);
		tex_pos += step;
		//color = texture[i][texture[i].height * tex_y + tex_x];
		color = get_texture_pixel(texture[texture->orientation], texture->tex_x, texture->tex_y);
		my_img_pixel_put(image, x, y, color);//buffer[y][x] = color;
		y++;
	}
}

void	choose_orientation(t_raycasting *ray, t_texture *texture)
{
	texture->orientation = 0;
	if (ray->side == 0)
	{
		if (ray->ray_x >= 0)
			texture->orientation = south;
		else
			texture->orientation = north;
	}
	else if (ray->side == 1)
	{
		if (ray->ray_y >= 0)
			texture->orientation = east;
		else
			texture->orientation = west;
	}
}

void	calculate_wall_x(t_player *player, t_raycasting *ray, t_texture *texture)
{
	if (ray->side == 0)
		texture->wall_x = player->y + ray->perp_wall_dist * ray->ray_y;
	else
		texture->wall_x = player->x + ray->perp_wall_dist * ray->ray_x;
	texture->wall_x -= floor(texture->wall_x);
}

void	calculate_x_coordinate_on_texture(t_raycasting *ray, t_texture *texture)
{
	texture->tex_x = (int)(texture->wall_x * (double)(texture[texture->orientation].width));
	if (ray->side == 0 && ray->ray_x > 0)
		texture->tex_x = texture[texture->orientation].width - texture->tex_x - 1;
	if (ray->side == 1 && ray->ray_y < 0)
		texture->tex_x = texture[texture->orientation].width - texture->tex_x - 1;
}

int	get_texture_pixel(t_texture texture, int x, int y)
{
	int	color;

	// Check out of texture coordinates
	if (x < 0 || x >= texture.width || y < 0 || y >= texture.height)
		return (0); // Returning black color
	color = (*(int *)(texture.addr + (y * texture.size_line) + (x * 4)));
	return (color);
}
