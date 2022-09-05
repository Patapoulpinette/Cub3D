/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:02:13 by dbouron           #+#    #+#             */
/*   Updated: 2022/06/02 11:22:57 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	degree_to_radian(int degree)
{
	return (degree * M_PI / 180);
}

double pythagoras(int a, int b)
{
	return (sqrt(pow(a, 2) + pow(b, 2)));
}

void	raycasting_algo(t_image *image, t_raycasting *raycasting)
{

}
