/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_ch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 17:53:01 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/11 18:01:39 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	search_ch(t_data *data, int j)
{
	int	c;

	c = data->map[data->i][j];
	if (c != '0' && c != '1' && c != 'N' && c != 'S' && c != 'E'
		&& c != 'W' && c != ' ' && c != '\n' && c != '\0')
		return (1);
	return (0);
}

int	search_ch_in_map(int j)
{
	if (j != '0' && j != '1' && j != 'N' && j != 'S' && j != 'E' && j != 'W')
		return (1);
	if (!j)
		return (1);
	return (0);
}

int	ch_is_inside(int j)
{
	if (j != '0' && j != 'N' && j != 'S' && j != 'E' && j != 'W')
		return (1);
	return (0);
}

int	ch_is_player(int j)
{
	if (j == 'N' || j == 'S' || j == 'E' || j == 'W')
		return (1);
	return (0);
}

int	ch_is_in_map(t_data *data, int i, int j)
{
	if (i != 0 && (int)ft_strlen(data->game_map[i - 1])
		>= j && data->game_map[i - 1][j] == '.')
		return (1);
	if (j != 0 && data->game_map[i][j - 1] == '.')
		return (1);
	if (j != (int)ft_strlen(data->game_map[i])
		&& data->game_map[i][j + 1] == '.')
		return (1);
	if (i != data->map_end && (int)ft_strlen(data->game_map[i + 1])
		>= j && data->game_map[i + 1][j] == '.')
		return (1);
	if (data->game_map[i][j] == '.')
		return (1);
	return (0);
}
