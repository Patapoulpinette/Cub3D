/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:46:14 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/21 17:49:42 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define mapWidth 24
#define mapHeight 24

void	load_texture(t_algo *algo)
{
	t_text	text1;
	int		color;
	//t_text	text2;

	
	text1.path = "textures/redbrick.xpm";
	//text2.path = "textures/bluestone.xpm";
	text1.img_ptr = mlx_xpm_file_to_image(algo->mlx.mlx_ptr, text1.path, &text1.width, &text1.height);
	//text2.img_ptr = mlx_xpm_file_to_image(algo->mlx.mlx_ptr, text2.path, &text2.width, &text2.height);
	text1.addr = mlx_get_data_addr(text1.img_ptr, &text1.bits_per_pixel, &text1.line_length, &text1.endian);
	//text2.addr = mlx_get_data_addr(text2.img_ptr, &text2.bits_per_pixel, &text2.line_length, &text2.endian);

	//(text1.addr[((y/COEFF) * 256) + ((x/COEFF) * 4)]) * 9000000
	const int COEFF = 4;
	for (int y = 0; y < (64 * COEFF); y++)
		for (int x = 0; x < (64 * COEFF); x++)
		{
			color = (*(int *)(text1.addr + ((y/COEFF) * text1.line_length) + ((x/COEFF) * 4)));
			my_mlx_pixel_put(&algo->mlx, x, y, color);
		}
	mlx_put_image_to_window(algo->mlx.mlx_ptr, algo->mlx.win_ptr, algo->mlx.img_ptr, 0, 0);
	mlx_put_image_to_window(algo->mlx.mlx_ptr, algo->mlx.win_ptr, text1.img_ptr, 0, 256);
	mlx_loop(algo->mlx.mlx_ptr);
}

int	initialisation(t_mlx *mlx, t_algo *algo)
{
	first_init(algo);
	srand(time(NULL));
	screen(algo->w, algo->h, &algo->mlx, "Raycaster");
	load_texture(algo);
	algoo(&algo->mlx, algo);
	mlx_hook(mlx->win_ptr, 2, 0L, key_hook, algo);
	mlx_loop(mlx->mlx_ptr);
	return (0);
}

int	algoo(t_mlx *mlx, t_algo *algo)
{
	int	x;
	int	color;

	x = -1;
	while(x++ < algo->w)
    {
    	second_init(algo, x);
		calc_dist_wall(algo);
		//perform DDA
		while (algo->hit == 0)
		{
			//jump to next map square, either in x-direction, or in y-direction
			if (algo->sideDistX < algo->sideDistY)
			{
				algo->sideDistX += algo->deltaDistX;
				algo->mapX += algo->stepX;
				algo->side = 0;
			}
			else
			{
				algo->sideDistY += algo->deltaDistY;
				algo->mapY += algo->stepY;
				algo->side = 1;
			}
			//Check if ray has hit a wall
			if (algo->data->f_game_map[algo->mapY][algo->mapX] == '1')
				algo->hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if(algo->side == 0)
			algo->perpWallDist = (algo->sideDistX - algo->deltaDistX);
		else
			algo->perpWallDist = (algo->sideDistY - algo->deltaDistY);
		//Calculate height of line to draw on screen
		algo->lineHeight = (int)(algo->h / algo->perpWallDist); //Calcule la longueur d'une ligne sur l'ecran (+ h est une grande valeur, plus les murs seront haut)				
		//Calcule le début de la ligne et la fin de la ligne (en prenant le milieu de l'ecran comme moitié)
		algo->drawStart = -algo->lineHeight / 2 + algo->h / 2;
		if(algo->drawStart < 0)
			algo->drawStart = 0;
		algo->drawEnd = algo->lineHeight / 2 + algo->h / 2;
		if(algo->drawEnd >= algo->h)
			algo->drawEnd = algo->h - 1;
		//give x and y sides different brightness
		if (algo->side == 1)
		{
			//color = 0x314159;
			color = 0x1e032e;
		}
		else
			//color = 0x612080;
			color = 0x131014;
		//draw the pixels of the stripe as a vertical line
		drawline(x, algo->drawStart, algo->drawEnd, color, mlx);
		//timing for input and FPS counter
		/* algo->oldTime = algo->time;
		algo->time = getTicks();
		double frameTime = (algo->time - algo->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / frameTime); //FPS counter */
		//redraw();
		//cls();			
		//speed modifiers
		/* double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second */
		
	}
	mlx_put_image_to_window(algo->mlx.mlx_ptr, algo->mlx.win_ptr, algo->mlx.img_ptr, 0, 0);
	return (0);
}
