/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:33:54 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/02 18:30:39 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc == 2)
	{
		parsing(&data, argv);
		display_window(&data);
	}
	else
		printf("Wrong number of arguments : ./cub3d [path_of_map]\n");
	return (0);
}

void	parsing(t_data *data, char **argv)
{
	name_error(argv[1]);
	count_line(data, argv[1]);
	backtracking(data);
	//debug(data);
	/* free_tab_c(data->game_map);
	free_tab_c(data->f_game_map);
	free(data->no_path);
	free(data->so_path);
	free(data->we_path);
	free(data->ea_path); */
}

void	name_error(char *maplink)
{
	int	i;

	i = ft_strlen(maplink);
	if (maplink[i - 1] != 'b' || maplink[i - 2] != 'u' || maplink[i - 3]
		!= 'c' || maplink[i - 4] != '.')
	{
		printf("%s\n%s\n", "Error", "The map is not a .cub");
		exit(0);
	}
}

void	debug(t_data *data)
{
	int	i;
	int	val;

	i = -1;
	val = -1;
	printf("  THE MAP :\n");
	while (data->game_map[++i])
	{
		printf("%s\n", data->game_map[i]);
	}
	printf("\n\nReal Map :\n\n");
	while (data->f_game_map[++val])
	{
		printf("%s\n", data->f_game_map[val]);
	}
	printf("\n  The paths :\n\n");
	printf("%s\n", data->no_path);
	printf("%s\n", data->so_path);
	printf("%s\n", data->we_path);
	printf("%s\n", data->ea_path);
	printf("\n  The colors :\n\n");
	printf("%d,%d,%d\n", data->ftabl[0], data->ftabl[1], data->ftabl[2]);
	printf("%d,%d,%d\n", data->ctabl[0], data->ctabl[1], data->ctabl[2]);
	printf("player orientation : %c\n", data->pl_orientation);
}

/* 
TODO
- change coordonates of player
- work on size of minimap to adapt with map size
- protect malloc, instructions which can fail
- do a function to free all mallocs when there is an error and the program quit (graphical_part.c)
- check leaks
- reorganize functions in files
- norme
- TESTS LIKE IN CORRECTION

TOFIX
- exec bug when go straight to the wall in front of player when orientation is W
- exec displays map error when the map doesn't end by a line of 1 enven if the map is closed before
- exec don't displays window when there is line of 1 before the first line of 1
 */