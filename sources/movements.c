/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 16:01:41 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/08 15:55:03 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(int key, t_structs *structs)
{
	if (key == 13)
	{
		structs->player->pdy--;
	}
	else if (key == 1)
	{
		structs->player->pdy++;
	}
}

void	translate_player(int key, t_structs *structs)
{
	if (key == 0)
	{
		structs->player->pdx--;
	}
	else if (key == 2)
	{
		structs->player->pdx++;
	}
}

/* void	rotate_camera_left(t_structs *structs)
{
	
}

void	rotate_camera_right(t_structs *structs)
{
	
}
 */