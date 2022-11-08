/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 04:19:59 by apercebo          #+#    #+#             */
/*   Updated: 2022/11/08 13:46:20 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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
	texturing_init(data);
	if (texturing(data) != 0)
		printf("Texture failed\n");
	if (map_parsing(data) == 1)
	{
		printf("MAP NOT CONFORM\n");
		exit(0);
	}
}

void	texturing_init(t_data *data)
{
	data->i = -1;
	data->no = 0;
	data->so = 0;
	data->we = 0;
	data->ea = 0;
	data->f = 0;
	data->c = 0;
}

int	texturing(t_data *data)
{
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
			if (data->map[data->i][data->j] && data->map[data->i][data->j] != '\n' && data->map[data->i][data->j] != ' ')
			{
				printf("Wrong map syntax\n");
				free_tab_c(data->map);
				exit(0);
			}
			if (data->map[data->i][data->j])
				data->j++;
		}
		if (data->no == 1 && data->so == 1 && data->we == 1
			&& data->ea == 1 && data->f == 1 && data->c == 1)
			return (0);
	}
	printf("Wrong map format\n");
	free_tab_c(data->map);
	exit(0);
}

int	map_parsing(t_data *data)
{
	if (skip_space(data) == 1)
		return (1);
	while (data->map[data->i++])
	{
		data->inc.j = -1;
		while (data->map[data->i] && data->map[data->i][++data->inc.j])
			if (search_ch(data, data->inc.j) == 1)
			{
				printf("%c\n", data->map[data->i][data->inc.j]);
				return (1);
			}
	}
	data->inc.j = -1;
	data->game_map = malloc(sizeof(char *) * (data->i - data->inc.save));
	data->map_end = data->i - data->inc.save - 2;
	//dprintf(2, "%s\n", data->map[data->inc.save]);
	malloc_map(data);
	if (map_error(data) == 1)
	{
		printf("Wrong map format\n");
		free_tab_c(data->game_map);
		exit(0);
	}
	return (0);
}
