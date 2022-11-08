/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:40:28 by apercebo          #+#    #+#             */
/*   Updated: 2022/11/08 16:56:09 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	backtracking(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->game_map[++i])
	{
		j = -1;
		while (data->game_map[i][++j])
			if (ch_is_player(data->game_map[i][j]) == 1)
				break ;
		if (data->game_map[i][j] && ch_is_player(data->game_map[i][j]) == 1)
			break ;
	}
	if (!data->game_map[i])
	{
		free_tab_c(data->game_map);
		error_exit();
	}
	data->pl_orientation = data->game_map[i][j];
	data->pl_x = i;
	data->pl_y = j;
	check_path(data, i, j);
	delete_walls(data);
	replace_dot(data);
	data->game_map[i][j] = data->pl_orientation;
}

void	replace_dot(t_data *data)
{
	data->inc.i = -1;
	while (data->f_game_map[++data->inc.i])
	{
		data->inc.j = -1;
		while (data->f_game_map[data->inc.i][++data->inc.j])
			if (data->f_game_map[data->inc.i][data->inc.j] == '.')
				data->f_game_map[data->inc.i][data->inc.j] = '0';
	}
}

void	check_path(t_data *data, int i, int j)
{
	data->game_map[i][j] = '.';
	if (data->game_map[i + 1][j] == '0')
		check_path(data, i + 1, j);
	if (data->game_map[i][j + 1] == '0')
		check_path(data, i, j + 1);
	if (data->game_map[i - 1][j] == '0')
		check_path(data, i - 1, j);
	if (data->game_map[i][j - 1] == '0')
		check_path(data, i, j - 1);
}

void	delete_walls2(t_data *data)
{
	data->f_game_map[data->inc.i] = NULL;
	data->inc.i = -1;
	while (data->f_game_map[++data->inc.i])
	{
		data->inc.j = -1;
		while (data->f_game_map[data->inc.i][++data->inc.j])
			if (ch_is_a_corner(data, data->inc.i, data->inc.j) == 1)
				data->f_game_map[data->inc.i][data->inc.j] = 'F';
	}
	data->inc.i = -1;
	while (data->f_game_map[++data->inc.i])
	{
		data->inc.j = -1;
		while (data->f_game_map[data->inc.i][++data->inc.j])
			if (data->f_game_map[data->inc.i][data->inc.j] == 'F')
				data->f_game_map[data->inc.i][data->inc.j] = '1';
	}
}

void	delete_walls(t_data *data)
{
	data->inc.i = -1;
	data->f_game_map = malloc(sizeof(char *) * (data->map_end + 2));
	if (!data->f_game_map)
		exit(EXIT_FAILURE);
	while (data->game_map[++data->inc.i])
	{
		data->inc.j = -1;
		data->f_game_map[data->inc.i] = malloc(sizeof(char)
				* (ft_strlen(data->game_map[data->inc.i]) + 1));
		if (!data->f_game_map[data->inc.i])
			exit(EXIT_FAILURE);
		while (data->game_map[data->inc.i][++data->inc.j])
		{
			if (ch_is_in_map(data, data->inc.i, data->inc.j) == 1)
				data->f_game_map[data->inc.i][data->inc.j]
					= data->game_map[data->inc.i][data->inc.j];
			else
				data->f_game_map[data->inc.i][data->inc.j] = ' ';
		}
		data->f_game_map[data->inc.i][data->inc.j] = '\0';
	}
	delete_walls2(data);
}
