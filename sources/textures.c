/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:52 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/21 17:57:50 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_textures(t_image *image, t_player *player, t_raycasting *ray, t_texture *texture, int x)
{
	int		i = 0;
	double	wall_x; //where exactly the wall was hit
	int		tex_x;
	int		tex_y;
	double	step;
	double	tex_pos;
	int		y;
	int		color;

	if (ray->side == 0)
	{
		i = north;
	}
	else if (ray->side == 1)
	{
		i = east;
	}

	//calculate value of wallX
	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_x;
	wall_x -= floor(wall_x);

	//x coordinate on the texture
	tex_x = (int)(wall_x * (double)(texture[i].width));
	if (ray->side == 0 && ray->ray_x > 0)
		tex_x = texture[i].width - tex_x - 1;
	if (ray->side == 1 && ray->ray_y < 0)
		tex_x = texture[i].width - tex_x - 1;

	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * texture[i].height / ray->line_height;

	// Starting texture coordinate
	tex_pos = (ray->draw_start - SCREEN_HEIGHT * 0.5 + ray->line_height * 0.5) * step;
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		tex_y = (int) tex_pos & (texture[i].height - 1);
		tex_pos += step;
		//color = texture[i][texture[i].height * tex_y + tex_x];
		color = get_texture_pixel(texture[i], tex_x, tex_y);
		my_img_pixel_put(image, x, y, color);//buffer[y][x] = color;
		y++;
	}
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
