/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:19:07 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/21 14:26:19 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	key_hook(int keycode, t_algo *algo)
{
	//dprintf(1, "KEYCODE : %d\n", keycode);
	if (keycode == 6)
    {
      if(algo->data->f_game_map[(int)(algo->posY)][(int)(algo->posX + algo->dirX * algo->moveSpeed)] == '0')
	  	algo->posX += algo->dirX * algo->moveSpeed;
      if(algo->data->f_game_map[(int)(algo->posY + algo->dirY * algo->moveSpeed)][(int)(algo->posX)] == '0')
	  	algo->posY += algo->dirY * algo->moveSpeed;
    }
	if (keycode == 1)
    {
      if(algo->data->f_game_map[(int)(algo->posY)][(int)(algo->posX - algo->dirX * algo->moveSpeed)] == '0')
	  	algo->posX -= algo->dirX * algo->moveSpeed;
      if(algo->data->f_game_map[(int)(algo->posY - algo->dirY * algo->moveSpeed)][(int)(algo->posX)] == '0')
	  	algo->posY -= algo->dirY * algo->moveSpeed;
    }
	//TRANSLATION
	if (keycode == 12)
    {
      if(algo->data->f_game_map[(int)(algo->posY)][(int)(algo->posX - algo->planeX * algo->moveSpeed)] == '0')
	  	algo->posX -= algo->planeX * algo->moveSpeed;
      if(algo->data->f_game_map[(int)(algo->posY - algo->planeY * algo->moveSpeed)][(int)(algo->posX)] == '0')
	  	algo->posY -= algo->planeY * algo->moveSpeed;
    }
	if (keycode == 2)
    {
      if(algo->data->f_game_map[(int)(algo->posY)][(int)(algo->posX + algo->planeX * algo->moveSpeed)] == '0')
	  	algo->posX += algo->planeX * algo->moveSpeed;
      if(algo->data->f_game_map[(int)(algo->posY + algo->planeY * algo->moveSpeed)][(int)(algo->posX)] == '0')
	  	algo->posY += algo->planeY * algo->moveSpeed;
    }
	//rotate to the right
    if (keycode == 124)
    {
      //both camera direction and camera plane must be rotated
      algo->oldDirX = algo->dirX;
      algo->dirX = algo->dirX * cos(-algo->rotSpeed) - algo->dirY * sin(-algo->rotSpeed);
      algo->dirY = algo->oldDirX * sin(-algo->rotSpeed) + algo->dirY * cos(-algo->rotSpeed);
      algo->oldPlaneX = algo->planeX;
      algo->planeX = algo->planeX * cos(-algo->rotSpeed) - algo->planeY * sin(-algo->rotSpeed);
      algo->planeY = algo->oldPlaneX * sin(-algo->rotSpeed) + algo->planeY * cos(-algo->rotSpeed);
    }
	//rotate to the left
    if (keycode == 123)
    {
      //both camera direction and camera plane must be rotated
      algo->oldDirX = algo->dirX;
      algo->dirX = algo->dirX * cos(algo->rotSpeed) - algo->dirY * sin(algo->rotSpeed);
      algo->dirY = algo->oldDirX * sin(algo->rotSpeed) + algo->dirY * cos(algo->rotSpeed);
      algo->oldPlaneX = algo->planeX;
      algo->planeX = algo->planeX * cos(algo->rotSpeed) - algo->planeY * sin(algo->rotSpeed);
      algo->planeY = algo->oldPlaneX * sin(algo->rotSpeed) + algo->planeY * cos(algo->rotSpeed);
    }
	algo->h = algo->h - 1;
	algo->h = algo->h + 1;
	algoo(&algo->mlx, algo);
	return (0);
}

/* void	algo_key();
{
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
 */