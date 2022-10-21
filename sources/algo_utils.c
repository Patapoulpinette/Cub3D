/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:36:26 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/21 14:07:04 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	first_init(t_algo *algo)
{
	algo->data->inc.i = -1;
	while (algo->data->f_game_map[++algo->data->inc.i])
	{
		algo->data->inc.j = -1;
		while (algo->data->f_game_map[algo->data->inc.i][++algo->data->inc.j])
			dprintf(1, "%c", algo->data->f_game_map[algo->data->inc.i][algo->data->inc.j]);
		dprintf(1, "\n");
	}
	algo->posX = 4.5; //Position du joueur (X et Y) 
	algo->posY = 6.5;
	dprintf(1, "\n POSITION -> %c\n\n", algo->data->f_game_map[6][4]);
	algo->dirX = -1; //Vecteur de direction (ex: dir y=1 signifie que le joueur regarde vers le haut de la carte)
	algo->dirY = 0;
	algo->planeX = 0; //Position du Camera plane (A droite ou a gauche de [pos + dir] ) {on peut le changer pour changer le FOV (ici fov=66degrès)}
	algo->planeY = 0.66;

 	algo->time = 0; //Temps de l'image actuel (Permet de calculer les fps en regardant le temps entre 2 images)
 	algo->oldTime = 0; //Temps de l'image précedente
	algo->w = 640; //w = largeur de l'écran
	algo->h = 480; //h = hauteur de l'écran
	algo->moveSpeed = 0.2;
	algo->rotSpeed = 0.08;
}

void	second_init(t_algo *algo, int x)
{
	//calculate ray position and direction
    algo->cameraX = 2 * x / algo->w - 1; //Position de X sur le camera plane
    algo->rayDirX = algo->dirX + algo->planeX * algo->cameraX; //Direction X du rayon
    algo->rayDirY = algo->dirY + algo->planeY * algo->cameraX; //Direction Y du rayon
	//which box of the map we're in
    algo->mapX = algo->posX; //X coordonné du carré de la map dans lequel on est situé
    algo->mapY = algo->posY; //Y coordonné du carré de la map dans lequel on est situé
    //length of ray from one x or y-side to next x or y-side
	if (algo->rayDirX == 0)  //Distance parcouru pour joindre les 2 cotés X d'un bloc
		algo->deltaDistX = 1e30;
    else 
		algo->deltaDistX = fabs(1 / algo->rayDirX);
	if (algo->rayDirY == 0) //Distance parcouru pour joindre les 2 cotés Y d'un bloc
		algo->deltaDistY = 1e30;
    else 
		algo->deltaDistY = fabs(1 / algo->rayDirY);
	algo->hit = 0; //Detecte si on a rencontré un mur
}

void	calc_dist_wall(t_algo *algo)
{
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
}
