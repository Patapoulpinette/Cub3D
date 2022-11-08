/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:03:39 by apercebo          #+#    #+#             */
/*   Updated: 2022/11/08 15:47:59 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ch_is_top(t_data *data)
{
	if (data->inc.i != 0 && (int)ft_strlen
		(data->game_map[data->inc.i - 1]) >= data->inc.j
		&& search_ch_in_map(data->game_map
			[data->inc.i - 1][data->inc.j]) == 1)
		return (1);
	if (data->inc.j != 0 && (search_ch_in_map(data->game_map
				[data->inc.i][data->inc.j - 1]) == 1))
		return (1);
	if (data->inc.j != (int)ft_strlen(data->game_map[data->inc.i])
		&& (search_ch_in_map(data->game_map
				[data->inc.i][data->inc.j + 1]) == 1))
		return (1);
	if ((data->inc.i != data->map_end && (int)
			ft_strlen(data->game_map[data->inc.i + 1])
			>= data->inc.j && search_ch_in_map(data->game_map
				[data->inc.i + 1][data->inc.j]) == 1))
		return (1);
	if (data->inc.i == 0 && (ch_is_inside(data->game_map
				[data->inc.i][data->inc.j]) == 0))
		return (1);
	if (data->inc.i == data->map_end
		&& (ch_is_inside(data->game_map[data->inc.i]
				[data->inc.j]) == 0))
		return (1);
	return (0);
}

int	ch_is_down(t_data *data)
{
	if (data->inc.j == 0 && (ch_is_inside(data->game_map
				[data->inc.i][data->inc.j]) == 0))
		return (1);
	if (data->inc.j == (int)ft_strlen(data->game_map[data->inc.i])
		&& (ch_is_inside(data->game_map[data->inc.i]
				[data->inc.j]) == 0))
		return (1);
	if (data->inc.i != 0 && (int)ft_strlen(data->game_map
			[data->inc.i - 1]) <= data->inc.j && ch_is_inside
		(data->game_map[data->inc.i][data->inc.j]) == 0)
		return (1);
	if (data->inc.i != data->map_end && (int)ft_strlen
		(data->game_map[data->inc.i + 1])
		<= data->inc.j && ch_is_inside(data->game_map
			[data->inc.i][data->inc.j]) == 0)
		return (1);
	return (0);
}

int	map_error(t_data *data)
{
	data->inc.i = -1;
	while (data->game_map[++data->inc.i])
	{
		data->inc.j = -1;
		while (data->game_map[data->inc.i][++data->inc.j])
		{
			if (ch_is_inside(data->game_map[data->inc.i][data->inc.j]) == 0)
			{
				if (ch_is_top(data) == 1)
					return (1);
				if (ch_is_down(data) == 1)
					return (1);
			}
		}
	}
	return (0);
}

int	skip_space(t_data *data)
{
	while (data->map[data->i][data->j++])
	{
		if (data->map[data->i][data->j] != ' ' && data->map[data->i][data->j]
			!= '\n')
			return (1);
	}
	while (data->map[++data->i])
	{
		data->j = -1;
		while (data->map[data->i][++data->j])
		{
			if (data->map[data->i][data->j] != ' '
				&& data->map[data->i][data->j] != '\n')
				break ;
		}
		if (data->map[data->i][data->j] && data->map[data->i][data->j]
			!= ' ' && data->map[data->i][data->j] != '\n')
			break ;
	}
	data->inc.save = data->i;
	return (0);
}

void	malloc_map(t_data *data)
{
	data->inc.j = -1;
	while (data->map[data->inc.save])
	{
		data->inc.j++;
		data->game_map[data->inc.j] = malloc(sizeof(char)
				* ((ft_strlen(data->map[data->inc.save]) + 1)));
		data->inc.x = -1;
		while (data->map[data->inc.save][++data->inc.x])
		{
			data->game_map[data->inc.j][data->inc.x] = data->map
			[data->inc.save][data->inc.x];
		}
		data->game_map[data->inc.j][data->inc.x] = data->map
		[data->inc.save][data->inc.x];
		data->inc.save++;
	}
	data->game_map[data->inc.j + 1] = NULL;
	//dprintf(2, "%s\n", data->game_map[1]);
	free_tab_c(data->map);
}
