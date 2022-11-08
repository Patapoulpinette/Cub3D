/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:37:54 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 17:19:40 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

void	ft_error(void)
{
	perror("");
	exit (-1);
}

int	ft_atoi(const char *str)
{
	int			nbr;
	long int	result;

	nbr = 0;
	result = 0;
	while (str[nbr] >= 48 && str[nbr] <= 57)
	{
		result = result * 10 + (str[nbr] - 48);
		nbr++;
	}
	return (result);
}

void	error_exit(void)
{
	printf("Wrong map format\n");
	exit(0);
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
