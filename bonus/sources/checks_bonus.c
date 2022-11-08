/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:06:57 by apercebo          #+#    #+#             */
/*   Updated: 2022/11/08 17:08:43 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	data_checks(t_data *data)
{
	if (data->no == 0)
		no_path(data);
	if (data->so == 0)
		so_path(data);
	if (data->we == 0)
		we_path(data);
	if (data->ea == 0)
		ea_path(data);
	if (data->f == 0)
		f_color(data);
	if (data->c == 0)
		c_color(data);
}
