/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:05:01 by dbouron           #+#    #+#             */
/*   Updated: 2022/08/23 21:59:51 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define X_RESOLUTION 5120
# define Y_RESOLUTION 2880

# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

typedef struct s_mlx_params
{
	void	*mlx;
	void	*window;
	int		x_win;
	int		y_win;
}				t_mlx_params;

typedef struct s_image
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		x_img;
	int		y_img;
}				t_image;

typedef struct s_maps_coord
{
	char	*name;
	int		**map_tab;
	int		x_len;
	int		y_len;
	int		x0;
	int		y0;
	int		x1;
	int		y1;
}				t_maps_coord;

typedef struct s_algo_params
{

}				t_algo_params;

typedef struct s_structs
{
	t_mlx_params	*mlx;
	t_image			*image;
	t_maps_coord	*map;
}				t_structs;

//parsing
void	parsing(t_maps_coord *map, char *str);

//graphical_part
void	create_image(t_mlx_params *mlx, t_image *image);
int		press_key(int key, t_structs *structs);
int		exit_program(void);
void	display_window(t_maps_coord *map);

//drawing_part


//algorithm


//bonus


//utils
size_t	ft_tablen(char **tab);
void	ft_error(void);

//free
void	free_tab_c(char **tab);
void	free_tab_i(int **tab, int size);

#endif
