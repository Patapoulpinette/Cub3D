/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 18:22:37 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 13:46:42 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	my_img_pixel_put(t_image *image, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= image->x_img || y >= image->y_img)
		return ;
	dst = image->addr + (y * image->size_line + x
			* (image->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
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

void	draw_fill_rect(t_image *image, t_dimensions *dim, int color)
{
	t_points	pt;
	int			wdth_coord;

	wdth_coord = dim->x + dim->width - 1;
	while (dim->x < wdth_coord)
	{
		pt.x0 = dim->x;
		pt.y0 = dim->y;
		pt.x1 = dim->x;
		pt.y1 = dim->y + dim->height - 2;
		bhm_line(image, &pt, color);
		dim->x++;
	}
}

void	draw_vertival_lines(t_image *image, t_raycasting *raycasting, int x)
{
	t_points	pt;

	//draw walls with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = raycasting->draw_start;
	pt.y1 = raycasting->draw_end;
	if (raycasting->side == 1) //give x and y sides different brightness
		bhm_line(image, &pt, WALL_COLOR * 0.5);
	else
		bhm_line(image, &pt, WALL_COLOR);
	//draw ceilling with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = 0;
	pt.y1 = raycasting->draw_start;
	bhm_line(image, &pt, raycasting->ceiling_color);
	//draw floor with vertical lines
	pt.x0 = x;
	pt.x1 = x;
	pt.y0 = raycasting->draw_end;
	pt.y1 = SCREEN_HEIGHT;
	bhm_line(image, &pt, raycasting->floor_color);
}
