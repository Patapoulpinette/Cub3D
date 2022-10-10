/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   backtracking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 11:40:28 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/10 14:25:34 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
	//printf("i: %d - j: %d", i, j); //POSITION DU PLAYER
	//display(data);
	check_path(data, i, j);
	delete_walls(data);
	data->game_map[i][j] = data->pl_orientation;
}

void	check_path(t_data *data, int i, int j)
{
	data->game_map[i][j] = 'X';
	int val = -1;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	while (data->game_map[++val])
	{
		printf("%s", data->game_map[val]);
	}
	usleep(15000);
	data->game_map[i][j] = '.';
	if (data->game_map[i + 1][j] == '0')
		check_path(data, i + 1, j);
	if (data->game_map[i][j + 1] == '0')
		check_path(data, i, j + 1);
	if (data->game_map[i - 1][j] == '0')
		check_path(data, i - 1, j);
	if (data->game_map[i][j - 1] == '0')
		check_path(data, i, j - 1);
	data->game_map[i][j] = 'X';
	int valeur = -1;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n");
	while (data->game_map[++valeur])
	{
		printf("%s", data->game_map[valeur]);
	}
	usleep(15000);
	data->game_map[i][j] = '.';
}

void	delete_walls(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->f_game_map = malloc(sizeof(char *) * (data->map_end + 2));
	while (data->game_map[++i])
	{
		j = -1;
		data->f_game_map[i] = malloc(sizeof(char) * (ft_strlen(data->game_map[i]) + 1));
		while (data->game_map[i][++j])
		{
			if (ch_is_in_map(data, i, j) == 1)
				data->f_game_map[i][j] = data->game_map[i][j];
			else
				data->f_game_map[i][j] = ' ';
		}
		data->f_game_map[i][j] = '\0';
	}
	data->f_game_map[i] = NULL;
	// |||||||||||||||||||||||||||||||||||||||||||||||||||||||
	i = -1;
	while (data->f_game_map[++i])
	{
		j = -1;
		while (data->f_game_map[i][++j])
			if (ch_is_a_corner(data, i, j) == 1)
				data->f_game_map[i][j] = 'F';
	}
	// |||||||||||||||||||||||||||||||||||||||||||||||||||||||
	i = -1;
	while (data->f_game_map[++i])
	{
		j = -1;
		while (data->f_game_map[i][++j])
			if (data->f_game_map[i][j] == 'F')
				data->f_game_map[i][j] = '1';
	}
	// |||||||||||||||||||||||||||||||||||||||||||||||||||||||
}

int	ch_is_a_corner(t_data *data, int i, int j)
{
	int	nbr;

	nbr = 0;
	if (data->f_game_map[i][j] != ' ')
		return (0);
	if (i != 0 && (int)ft_strlen(data->f_game_map[i - 1]) >= j && data->f_game_map[i - 1][j] == '1')
		nbr++;
	if (j != 0 && data->f_game_map[i][j - 1] == '1')
		nbr++;
	if (j != (int)ft_strlen(data->f_game_map[i]) && data->f_game_map[i][j + 1] == '1')
		nbr++;
	if (i != data->map_end && (int)ft_strlen(data->f_game_map[i + 1]) >= j && data->f_game_map[i + 1][j] == '1')
		nbr++;
	if (nbr > 1)
		return (1);
	return (0);
}

int	ch_is_in_map(t_data *data, int i, int j)
{
	if (i != 0 && (int)ft_strlen(data->game_map[i - 1]) >= j && data->game_map[i - 1][j] == '.')
		return (1);
	if (j != 0 && data->game_map[i][j - 1] == '.')
		return (1);
	if (j != (int)ft_strlen(data->game_map[i]) && data->game_map[i][j + 1] == '.')
		return (1);
	if (i != data->map_end && (int)ft_strlen(data->game_map[i + 1]) >= j && data->game_map[i + 1][j] == '.')
		return (1);
	if (data->game_map[i][j] == '.')
		return (1);
	return (0);
}

int	ch_is_player(int j)
{
	if (j == 'N' || j == 'S' || j == 'E' || j == 'W')
		return (1);
	return (0);
}
