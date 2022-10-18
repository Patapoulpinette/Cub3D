/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 16:37:52 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/17 18:55:36 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* void	draw_textures(t_image *image, t_player *player, t_raycasting *ray, t_texture *texture)
{
	double			wall_x; //where exactly the wall was hit
	int				tex_x;
	int				tex_y;
	double			step;
	double			tex_pos;
	int				y;
	unsigned int	color;

	//calculate value of wallX
	if (ray->side == 0)
		wall_x = player->y + ray->perp_wall_dist * ray->ray_y;
	else
		wall_x = player->x + ray->perp_wall_dist * ray->ray_x;
	wall_x -= floor(wall_x);

	//x coordinate on the texture
	tex_x = (int) (wall_x * (double) (texture->width));
	if (ray->side == 0 && ray->ray_x > 0)
		tex_x = texture->width - tex_x - 1;
	if (ray->side == 1 && ray->ray_y < 0)
		tex_x = texture->width - tex_x - 1;

	// How much to increase the texture coordinate per screen pixel
	step = 1.0 * texture->height / ray->line_height;
	
	// Starting texture coordinate
	tex_pos = (ray->draw_start - 100 - SCREEN_HEIGHT * 0.5 + ray->line_height * 0.5) * step;// 100 = pitch (je ne sais pas à quoi ça sert)
	y = ray->draw_start;
	while (y < ray->draw_end)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		tex_y = (int)tex_pos & (texture->height - 1);
		tex_pos += step;
		if (ray->side == 0)
			color = texture->catalog[0][texture->height * tex_y + tex_x];
		if(ray->side == 1)
			color = texture->catalog[1][texture->height * tex_y + tex_x];
		my_img_pixel_put(image, ?, ?, color);//buffer[y][x] = color;
		y++;
	}

	//drawBuffer(buffer[0]);
	//for(int y = 0; y < SCREEN_HEIGHT; y++) for(int x = 0; x < SCREEN_WIDTH; x++) buffer[y][x] = 0; //clear the buffer instead of cls()
} */
