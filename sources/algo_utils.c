/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 15:36:26 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/17 15:36:46 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	first_init(t_algo *algo)
{
	algo->posX = 22; //Position du joueur (X et Y) 
	algo->posY = 12;
	algo->dirX = -1; //Vecteur de direction (ex: dir y=1 signifie que le joueur regarde vers le haut de la carte)
	algo->dirY = 0;
	algo->planeX = 0; //Position du Camera plane (A droite ou a gauche de [pos + dir] ) {on peut le changer pour changer le FOV (ici fov=66degrès)}
	algo->planeY = 0.66;

 	algo->time = 0; //Temps de l'image actuel (Permet de calculer les fps en regardant le temps entre 2 images)
 	algo->oldTime = 0; //Temps de l'image précedente
	algo->w = 640; //w = largeur de l'écran
	algo->h = 480; //h = hauteur de l'écran
}
