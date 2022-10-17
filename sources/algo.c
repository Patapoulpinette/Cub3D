/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:46:14 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/17 16:09:38 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define mapWidth 24
#define mapHeight 24

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

void	screen(int sWidth, int sHeight, t_mlx *mlx, char *str)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, sWidth, sHeight, str);
}

int	algoo(t_mlx *mlx, t_algo *algo)
{
	int	x;

	first_init(algo);
	screen(algo->w, algo->h, &mlx, "Raycaster");
	while(!done())
  	{
		x = 0;
		while(x < algo->w)
		for(int x = 0; x < algo->w; x++)
    	{
    		second_init(algo, x);
			//calculate step and initial sideDist
			if (algo->rayDirX < 0)
			{
				algo->stepX = -1;
				algo->sideDistX = (algo->posX - algo->mapX) * algo->deltaDistX; //Calcule la distance entre le joueur et le mur
			}
			else
			{
				algo->stepX = 1;
				algo->sideDistX = (algo->mapX + 1.0 - algo->posX) * algo->deltaDistX; //Calcule la distance entre le joueur et le mur
			}
			if (algo->rayDirY < 0)
			{
				algo->stepY = -1;
				algo->sideDistY = (algo->posY - algo->mapY) * algo->deltaDistY; //Calcule la distance entre le joueur et le mur
			}
			else
			{
				algo->stepY = 1;
				algo->sideDistY = (algo->mapY + 1.0 - algo->posY) * algo->deltaDistY; //Calcule la distance entre le joueur et le mur
			}
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
				if (worldMap[algo->mapX][algo->mapY] > 0) algo->hit = 1;
				//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
				if(algo->side == 0) algo->perpWallDist = (algo->sideDistX - algo->deltaDistX);
				else          algo->perpWallDist = (algo->sideDistY - algo->deltaDistY);
				//Calculate height of line to draw on screen
				int lineHeight = (int)(algo->h / algo->perpWallDist) //Calcule la longueur d'une ligne sur l'ecran (+ h est une grande valeur, plus les murs seront haut)				
				//Calcule le début de la ligne et la fin de la ligne (en prenant le milieu de l'ecran comme moitié)
				int drawStart = -lineHeight / 2 + h / 2;
				if(drawStart < 0)drawStart = 0;
				int drawEnd = lineHeight / 2 + h / 2;
				if(drawEnd >= h)drawEnd = h - 1;
				//choose wall color
				ColorRGB color;
				switch(worldMap[algo->mapX][algo->mapY])
				{
					case 1:  color = RGB_Red;  break; //red
					case 2:  color = RGB_Green;  break; //green
					case 3:  color = RGB_Blue;   break; //blue
					case 4:  color = RGB_White;  break; //white
					default: color = RGB_Yellow; break; //yellow
				}
				//give x and y sides different brightness
				if (side == 1) {color = color / 2};				
				//draw the pixels of the stripe as a vertical line
				verLine(x, drawStart, drawEnd, color);
			}
			//timing for input and FPS counter
			algo->oldTime = algo->time;
			algo->time = getTicks();
			double frameTime = (algo->time - algo->oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
			print(1.0 / frameTime); //FPS counter
			redraw();
			cls();			
			//speed modifiers
			double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
			double rotSpeed = frameTime * 3.0; //the constant value is in radians/second

			readKeys();
    		//move forward if no wall in front of you
    		if (keyDown(SDLK_UP))
    		{
    		  if(worldMap[int(algo->posX + algo->dirX * moveSpeed)][int(algo->posY)] == false) algo->posX += algo->dirX * moveSpeed;
    		  if(worldMap[int(algo->posX)][int(algo->posY + algo->dirY * moveSpeed)] == false) algo->posY += algo->dirY * moveSpeed;
    		}
    		//move backwards if no wall behind you
    		if (keyDown(SDLK_DOWN))
    		{
    		  if(worldMap[int(algo->posX - algo->dirX * moveSpeed)][int(algo->posY)] == false) algo->posX -= algo->dirX * moveSpeed;
    		  if(worldMap[int(algo->posX)][int(algo->posY - algo->dirY * moveSpeed)] == false) algo->posY -= algo->dirY * moveSpeed;
    		}
    		//rotate to the right
    		if (keyDown(SDLK_RIGHT))
    		{
    		  //both camera direction and camera plane must be rotated
    		  double oldDirX = algo->dirX;
    		  algo->dirX = algo->dirX * cos(-rotSpeed) - algo->dirY * sin(-rotSpeed);
    		  algo->dirY = oldDirX * sin(-rotSpeed) + algo->dirY * cos(-rotSpeed);
    		  double oldPlaneX = algo->planeX;
    		  algo->planeX = algo->planeX * cos(-rotSpeed) - algo->planeY * sin(-rotSpeed);
    		  algo->planeY = oldPlaneX * sin(-rotSpeed) + algo->planeY * cos(-rotSpeed);
    		}
    		//rotate to the left
    		if (keyDown(SDLK_LEFT))
    		{
    		  //both camera direction and camera plane must be rotated
    		  double oldDirX = algo->dirX;
    		  algo->dirX = algo->dirX * cos(rotSpeed) - algo->dirY * sin(rotSpeed);
    		  algo->dirY = oldDirX * sin(rotSpeed) + algo->dirY * cos(rotSpeed);
    		  double oldPlaneX = algo->planeX;
    		  algo->planeX = algo->planeX * cos(rotSpeed) - algo->planeY * sin(rotSpeed);
    		  algo->planeY = oldPlaneX * sin(rotSpeed) + algo->planeY * cos(rotSpeed);
    		}
			
		}
	}
}
