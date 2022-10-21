/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 09:19:29 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/21 16:34:57 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	screen(int sWidth, int sHeight, t_mlx *mlx, char *str)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, sWidth, sHeight, str);
	mlx->img_ptr = mlx_new_image(mlx, 640, 480);
	mlx->addr = mlx_get_data_addr(mlx->img_ptr, &mlx->bits_per_pixel, &mlx->line_length, &mlx->endian);
}

void	my_mlx_pixel_put(t_mlx *mlx, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= 640 || y >= 480)
		return ;
	dst = mlx->addr + (y * mlx->line_length + x * 4	);
	*(unsigned int*)dst = color;
}

void	drawline(int x, int drawStart, int drawEnd, int color, t_mlx *mlx)
{
	int	i;

	i = 0;
	while (i < drawStart)
	{
		if (rand() % 342 == 0)
		//if (i % 42 == 0)
			my_mlx_pixel_put(mlx, x, i, 0xFFFFFF);
		else
			my_mlx_pixel_put(mlx, x, i, 0x08034d);
		i++;
	}
	while (i < drawEnd)
	{
		my_mlx_pixel_put(mlx, x, i, color);
		i++;
	}
	while (i < 480)
	{
		if (i % 6 == 0)
			my_mlx_pixel_put(mlx, x, i, 0x000000);
		else
			my_mlx_pixel_put(mlx, x, i, 0x2d2d2e);
		i++;
	}
}
