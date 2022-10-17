/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:46:14 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/17 15:47:46 by apercebo         ###   ########.fr       */
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
	first_init(algo);
	screen(algo->w, algo->h, &mlx, "Raycaster");
	while(!done())
  	{
		for(int x = 0; x < algo->w; x++)
    	{
    		//calculate ray position and direction
    		double cameraX = 2 * x / algo->w - 1; //Position de X sur le camera plane
    		double rayDirX = algo->dirX + algo->planeX * cameraX; //Direction X du rayon
    		double rayDirY = algo->dirY + algo->planeY * cameraX; //Direction Y du rayon
			//which box of the map we're in
    		int mapX = algo->posX; //X coordonné du carré de la map dans lequel on est situé
    		int mapY = algo->posY; //Y coordonné du carré de la map dans lequel on est situé

    		//length of ray from current position to next x or y-side
    		double sideDistX; //Distance initial que le rayon a à parcourir avant d'atteindre le prochain carré en X
    		double sideDistY; //Distance initial que le rayon a à parcourir avant d'atteindre le prochain carré en Y

    		 //length of ray from one x or y-side to next x or y-side
    		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX); //Distance parcouru pour joindre les 2 cotés X d'un bloc
    		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY); //Distance parcouru pour joindre les 2 cotés Y d'un bloc
    		double perpWallDist; // Utile pour calculer la longueur du rayon (et donc la distance entre le joueur et le mur)

    		//what direction to step in x or y-direction (either +1 or -1)
    		int stepX; //La direction dans lequel est le prochain mur (1 = on va à droite, -1 = on va à gauche)
    		int stepY; //La direction dans lequel est le prochain mur (1 = on monte, -1 = on descend)

    		int hit = 0; //Detecte si on a rencontré un mur
    		int side; //Determine de quel coté un mur a été toucher (0 = gauche/droite | 1 = haut/bas)

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (algo->posX - mapX) * deltaDistX; //Calcule la distance entre le joueur et le mur
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - algo->posX) * deltaDistX; //Calcule la distance entre le joueur et le mur
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (algo->posY - mapY) * deltaDistY; //Calcule la distance entre le joueur et le mur
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - algo->posY) * deltaDistY; //Calcule la distance entre le joueur et le mur
			}
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
				//Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
				if(side == 0) perpWallDist = (sideDistX - deltaDistX);
				else          perpWallDist = (sideDistY - deltaDistY);
				//Calculate height of line to draw on screen
				int lineHeight = (int)(h / perpWallDist) //Calcule la longueur d'une ligne sur l'ecran (+ h est une grande valeur, plus les murs seront haut)				
				//Calcule le début de la ligne et la fin de la ligne (en prenant le milieu de l'ecran comme moitié)
				int drawStart = -lineHeight / 2 + h / 2;
				if(drawStart < 0)drawStart = 0;
				int drawEnd = lineHeight / 2 + h / 2;
				if(drawEnd >= h)drawEnd = h - 1;
				//choose wall color
				ColorRGB color;
				switch(worldMap[mapX][mapY])
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
