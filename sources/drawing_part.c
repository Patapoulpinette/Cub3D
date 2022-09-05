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

/*static void	ft_test(t_image *image)
{
	t_points points;

	//SKY-----------------------------------------------
	points.x0 = 0;
	points.y0 = 0;
	points.x1 = 0;
	points.y1 = 150;
	while (points.x0 <= 200)
	{
		bhm_line(image, &points, SKY_COLOR);

		points.x0++;
		points.x1++;
		if (points.x1 % 2 == 0)
			points.y1--;
	}
	while (points.x0 <= 440)
	{
		bhm_line(image, &points, SKY_COLOR);

		points.x0++;
		points.x1++;
	}
	while (points.x0 <= 640)
	{
		bhm_line(image, &points, SKY_COLOR);

		points.x0++;
		points.x1++;
		if (points.x1 % 2 == 0)
			points.y1++;
	}

	//WALL--------------------------------------------------
	points.x0 = 0;
	points.y0 = 150;
	points.x1 = 0;
	points.y1 = 400;
	while (points.x0 <= 200)
	{
		bhm_line(image, &points, WALL_COLOR);

		points.x0++;
		points.x1++;
		points.y1--;
		if (points.x1 % 2 == 0)
			points.y0--;
	}
	while (points.x0 <= 440)
	{
		bhm_line(image, &points, WALL_COLOR);

		points.x0++;
		points.x1++;
	}
	while (points.x0 <= 640)
	{
		bhm_line(image, &points, WALL_COLOR);

		points.x0++;
		points.x1++;
		points.y1++;
		if (points.x1 % 2 == 0)
			points.y0++;
	}

	//FLOOR--------------------------------------------------
	points.x0 = 0;
	points.y0 = 400;
	points.x1 = 0;
	points.y1 = 480;
	while (points.x0 <= 200)
	{
		bhm_line(image, &points, FLOOR_COLOR);

		points.x0++;
		points.x1++;
		points.y0--;
	}
	while (points.x0 <= 440)
	{
		bhm_line(image, &points, FLOOR_COLOR);

		points.x0++;
		points.x1++;
	}
	while (points.x0 <= 640)
	{
		bhm_line(image, &points, FLOOR_COLOR);

		points.x0++;
		points.x1++;
		points.y0++;
	}

	//CONTOUR WALL
	points.x0 = 0;
	points.y0 = 150;
	points.x1 = 0;
	points.y1 = 400;
	bhm_line(image, &points, 0x000000);
	points.x0 = 200;
	points.y0 = 50;
	points.x1 = 200;
	points.y1 = 199;
	bhm_line(image, &points, 0x000000);
	points.x0 = 0;
	points.y0 = 150;
	points.x1 = 200;
	points.y1 = 50;
	bhm_line(image, &points, 0x000000);
	points.x0 = 0;
	points.y0 = 400;
	points.x1 = 200;
	points.y1 = 199;
	bhm_line(image, &points, 0x000000);
	points.x0 = 200;
	points.y0 = 50;
	points.x1 = 440;
	points.y1 = 50;
	bhm_line(image, &points, 0x000000);
	points.x0 = 200;
	points.y0 = 199;
	points.x1 = 440;
	points.y1 = 199;
	bhm_line(image, &points, 0x000000);
	points.x0 = 440;
	points.y0 = 50;
	points.x1 = 440;
	points.y1 = 199;
	bhm_line(image, &points, 0x000000);
	points.x0 = 440;
	points.y0 = 50;
	points.x1 = 640;
	points.y1 = 150;
	bhm_line(image, &points, 0x000000);
	points.x0 = 440;
	points.y0 = 199;
	points.x1 = 640;
	points.y1 = 399;
	bhm_line(image, &points, 0x000000);
	points.x0 = 640;
	points.y0 = 150;
	points.x1 = 640;
	points.y1 = 399;
	bhm_line(image, &points, 0x000000);
}*/

void	draw_in_image(t_image *image, t_raycasting *raycasting)
{
	//(void) image;
	//(void) raycasting;

	raycasting_algo(image, raycasting);

	//ft_test(image);
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
