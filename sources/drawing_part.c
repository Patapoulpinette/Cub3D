/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_part.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 18:43:02 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/08 15:45:07 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_in_image(t_mlx *mlx, t_image *image, t_player *player, t_raycasting *raycasting)
{
	mlx_clear_window(mlx->mlx, mlx->window);
	draw_player(image, player, raycasting);
	//raycasting_algo(image, raycasting);
	mlx_put_image_to_window(mlx->mlx, mlx->window, image->img, 0, 0);
}

void	draw_player(t_image *image, t_player *player, t_raycasting *raycasting)
{
	(void) raycasting;
	my_img_pixel_put(image, player->px + player->pdx * 10, \
		player->py + player->pdy * 10, 0xbde0fe);
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
