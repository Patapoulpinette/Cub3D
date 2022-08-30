/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:05:01 by dbouron           #+#    #+#             */
/*   Updated: 2022/08/25 11:38:21 by dbouron          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define SCREEN_HALF_WIDTH 640 / 2
# define SCREEN_HALF_HEIGHT 480 / 2

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
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	dx1;
	int	dy1;
	int	px;
	int	py;
	int	xe;
	int	ye;
	//*************************************
	time_t	render_delay;
	int		player_FOV;
	int		player_half_FOV;
	int		player_X; //à enlever à terme car viendra de la map parsée
	int		player_Y; //à enlever à terme car viendra de la map parsée
	int		player_angle; //à enlever à terme car viendra de la map parsée
	int		rayCasting_increment_angle;
	int		rayCasting_precision;
	char	**map; //à enlever à terme car viendra de la map parsée
}				t_algo_params;

typedef struct s_points
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_points;

typedef struct s_structs
{
	t_mlx_params	*mlx;
	t_image			*image;
	//t_maps_coord	*map;
}				t_structs;

//parsing

//initializing
void	initialize_values(t_algo_params *algo_params);

//graphical_part
void	create_image(t_mlx_params *mlx, t_image *image);
int		press_key(int key, t_structs *structs);
int		exit_program(void);
void	display_window(void); //t_maps_coord *map

//drawing_part
void	draw_in_image(t_image *image);
void	my_img_pixel_put(t_image *image, int x, int y, int color);

//algorithm
void	bhm_line(t_image *image, t_points *pt, int color);

//bonus


//utils
size_t	ft_tablen(char **tab);
void	ft_error(void);

//free
void	free_tab_c(char **tab);
void	free_tab_i(int **tab, int size);

#endif
