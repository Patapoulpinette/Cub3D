/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:40:28 by apercebo          #+#    #+#             */
/*   Updated: 2022/11/03 15:58:48 by dbouron          ###   ########lyon.fr   */
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
	data->pl_orientation = data->game_map[i][j];
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
	while (data->game_map[++data->inc.i])
	{
		data->inc.j = -1;
		data->f_game_map[data->inc.i] = malloc(sizeof(char)
				* (ft_strlen(data->game_map[data->inc.i]) + 1));
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

int	ch_is_a_corner(t_data *data, int i, int j)
{
	int	nbr;

	nbr = 0;
	if (data->f_game_map[i][j] != ' ')
		return (0);
	if (i != 0 && (int)ft_strlen(data->f_game_map[i - 1])
		>= j && data->f_game_map[i - 1][j] == '1')
		nbr++;
	if (j != 0 && data->f_game_map[i][j - 1] == '1')
		nbr++;
	if (j != (int)ft_strlen(data->f_game_map[i])
		&& data->f_game_map[i][j + 1] == '1')
		nbr++;
	if (i != data->map_end && (int)ft_strlen(data->f_game_map[i + 1])
		>= j && data->f_game_map[i + 1][j] == '1')
		nbr++;
	if (nbr > 1)
		return (1);
	return (0);
}
