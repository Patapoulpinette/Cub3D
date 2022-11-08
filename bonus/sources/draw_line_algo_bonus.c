/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_line_algo_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 13:46:47 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

static void	drawline_1(t_image *image, t_points *pt, t_line_algo *algo, \
					int color)
{
	if (algo->dx >= 0)
	{
		algo->x = pt->x0;
		algo->y = pt->y0;
		algo->xe = pt->x1;
	}
	else
	{
		algo->x = pt->x1;
		algo->y = pt->y1;
		algo->xe = pt->x0;
	}
	my_img_pixel_put(image, algo->x, algo->y, color);
}

static void	drawline_2(t_image *image, t_line_algo *algo, int color)
{
	while (algo->x < algo->xe)
	{
		algo->x = algo->x + 1;
		if (algo->px < 0)
			algo->px = algo->px + 2 * algo->dy1;
		else
		{
			if ((algo->dx < 0 && algo->dy < 0) \
					|| (algo->dx > 0 && algo->dy > 0))
				algo->y = algo->y + 1;
			else
				algo->y = algo->y - 1;
			algo->px = algo->px + 2 * (algo->dy1 - algo->dx1);
		}
		my_img_pixel_put(image, algo->x, algo->y, color);
	}
}

static void	drawline_3(t_image *image, t_points *pt, t_line_algo *algo, \
					int color)
{
	if (algo->dy >= 0)
	{
		algo->x = pt->x0;
		algo->y = pt->y0;
		algo->ye = pt->y1;
	}
	else
	{
		algo->x = pt->x1;
		algo->y = pt->y1;
		algo->ye = pt->y0;
	}
	my_img_pixel_put(image, algo->x, algo->y, color);
}

static void	drawline_4(t_image *image, t_line_algo *algo, int color)
{
	while (algo->y < algo->ye)
	{
		algo->y = algo->y + 1;
		if (algo->py <= 0)
			algo->py = algo->py + 2 * algo->dx1;
		else
		{
			if ((algo->dx < 0 && algo->dy < 0) \
					|| (algo->dx > 0 && algo->dy > 0))
				algo->x = algo->x + 1;
			else
				algo->x = algo->x - 1;
			algo->py = algo->py + 2 * (algo->dx1 - algo->dy1);
		}
		my_img_pixel_put(image, algo->x, algo->y, color);
	}
}

void	bhm_line(t_image *image, t_points *pt, int color)
{
	t_line_algo	algo;

	algo.dx = pt->x1 - pt->x0;
	algo.dy = pt->y1 - pt->y0;
	algo.dx1 = abs(algo.dx);
	algo.dy1 = abs(algo.dy);
	algo.px = 2 * algo.dy1 - algo.dx1;
	algo.py = 2 * algo.dx1 - algo.dy1;
	if (algo.dy1 <= algo.dx1)
	{
		drawline_1(image, pt, &algo, color);
		drawline_2(image, &algo, color);
	}
	else
	{
		drawline_3(image, pt, &algo, color);
		drawline_4(image, &algo, color);
	}
}
