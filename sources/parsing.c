/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 04:19:59 by apercebo          #+#    #+#             */
/*   Updated: 2022/10/11 18:02:14 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	count_line(t_data *data, char *maplink)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(maplink, O_RDONLY);
	if (fd < 0)
	{
		printf("%s\n%s\n", "Error", "The map does not exist");
		exit(0);
	}
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		i++;
		free(line);
	}
	free(line);
	recup_map(data, fd, i, maplink);
}

void	recup_map(t_data *data, int fd, int i, char *maplink)
{
	data->height = i;
	data->map = malloc(sizeof(char *) * (i + 1));
	if (!data->map)
	{
		printf("%s\n%s\n", "Error", "Malloc error");
		exit(0);
	}
	close(fd);
	fd = open(maplink, O_RDONLY);
	i = 0;
	while (1)
	{
		data->map[i] = get_next_line(fd);
		if (data->map[i] == NULL)
			break ;
		i++;
	}
	if (texturing(data) == 0)
		printf("SUCCESS\n");
	if (map_parsing(data) == 1)
	{
		printf("MAP NOT CONFORM\n");
		exit(0);
	}
}

int	texturing(t_data *data)
{
	data->i = -1;
	data->no = 0;
	data->so = 0;
	data->we = 0;
	data->ea = 0;
	data->f = 0;
	data->c = 0;
	while (data->map[++data->i])
	{
		data->j = 0;
		while (data->map[data->i][data->j])
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
			if (data->map[data->i][data->j])
				data->j++;
		}
		if (data->no == 1 && data->so == 1 && data->we == 1
			&& data->ea == 1 && data->f == 1 && data->c == 1)
			return (0);
	}
	return (1);
}

int	map_parsing(t_data *data)
{
	int	save;
	int	j;
	int	x;

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
	save = data->i;
	while (data->map[data->i++])
	{
		j = -1;
		while (data->map[data->i] && data->map[data->i][++j])
			if (search_ch(data, j) == 1)
				return (1);
	}
	j = -1;
	data->game_map = malloc(sizeof(char *) * (data->i - save));
	data->map_end = data->i - save - 2;
	dprintf(2, "%s\n", data->map[save]);
	j = -1;
	while (data->map[save])
	{
		j++;
		data->game_map[j] = malloc(sizeof(char)
				* ((ft_strlen(data->map[save]) + 1)));
		x = -1;
		while (data->map[save][++x])
		{
			data->game_map[j][x] = data->map[save][x];
		}
		data->game_map[j][x] = data->map[save][x];
		save++;
	}
	data->game_map[j + 1] = NULL;
	dprintf(2, "%s\n", data->game_map[1]);
	j = -1;
	while (data->map[++j])
		free(data->map[j]);
	free(data->map);
	if (map_error(data) == 1)
	{
		printf("ERROR MAP\n");
		exit(0);
	}
	return (0);
}

int	map_error(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	while (data->game_map[++i])
	{
		j = -1;
		while (data->game_map[i][++j])
		{
			if (ch_is_inside(data->game_map[i][j]) == 0)
			{
				if (i != 0 && (int)ft_strlen(data->game_map[i - 1])
					>= j && search_ch_in_map(data->game_map[i - 1][j]) == 1)
					return (1);
				if (j != 0 && (search_ch_in_map(data->game_map[i][j - 1]) == 1))
					return (1);
				if (j != (int)ft_strlen(data->game_map[i])
					&& (search_ch_in_map(data->game_map[i][j + 1]) == 1))
					return (1);
				if ((i != data->map_end && (int)ft_strlen(data->game_map[i + 1])
						>= j && search_ch_in_map(data->game_map[i + 1][j])
					== 1))
					return (1);
				if (i == 0 && (ch_is_inside(data->game_map[i][j]) == 0))
					return (1);
				if (i == data->map_end
					&& (ch_is_inside(data->game_map[i][j]) == 0))
					return (1);
				if (j == 0 && (ch_is_inside(data->game_map[i][j]) == 0))
					return (1);
				if (j == (int)ft_strlen(data->game_map[i])
					&& (ch_is_inside(data->game_map[i][j]) == 0))
					return (1);
				if (i != 0 && (int)ft_strlen(data->game_map[i - 1])
					<= j && ch_is_inside(data->game_map[i][j]) == 0)
					return (1);
				if (i != data->map_end && (int)ft_strlen(data->game_map[i + 1])
					<= j && ch_is_inside(data->game_map[i][j]) == 0)
					return (1);
			}
		}
	}
	return (0);
}
