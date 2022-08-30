/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/03 11:32:33 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_image *image)
{
	t_points points;

	points.x0 = 100;
	points.y0 = 100;
	points.x1 = 200;
	points.y1 = 100;
	bhm_line(image, &points, 0xffc8dd);
	points.x1 = 100;
	points.y1 = 200;
	bhm_line(image, &points, 0xffc8dd);
	points.x0 = 200;
	points.y0 = 200;
	bhm_line(image, &points, 0xffc8dd);
	points.x1 = 200;
	points.y1 = 100;
	bhm_line(image, &points, 0xffc8dd);
	points.x1 = 300;
	points.y1 = 300;
	bhm_line(image, &points, 0xffc8dd9);
}

void	my_img_pixel_put(t_image *image, int x, int y, int color)
{
	char *dst;

	if (x < 0 || y < 0 || x >= image->x_img || y >= image->y_img)
		return;
	dst = image->addr + (y * image->size_line + x
			* (image->bits_per_pixel / 8));
	*(unsigned int *) dst = color;
}
