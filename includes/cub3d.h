/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:05:01 by dbouron           #+#    #+#             */
/*   Updated: 2022/09/12 15:53:23 by dbouron          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define FLOOR_COLOR 0xdda15e
# define WALL_COLOR 0x606c38
# define SKY_COLOR 0xbde0fe

typedef struct s_mlx
{
	void	*mlx;
	void	*window;
	int		x_win;
	int		y_win;
}				t_mlx;

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
	char	**map_tab;
}				t_maps_coord;

typedef struct s_line_algo
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
}				t_line_algo;

typedef struct s_raycasting
{
	double	player_x;
	double	player_y;
	double	direction_x;
	double	direction_y;
	double	camera_plane_x;
	double	camera_plane_y;
	double	move_speed;
	double	rot_speed;
	int		side;
	int		draw_start;
	int		draw_end;
}				t_raycasting;

typedef struct s_player
{
	int	px;
	int	py;
	int	pdx;
	int	pdy;
	int	pa;
}				t_player;

typedef struct s_minimap
{
	int		map_x;
	int		map_y;
	char	**map;
	int		ray;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
}				t_minimap;

typedef struct s_structs
{
	t_mlx			*mlx;
	t_image			*image;
	//t_maps_coord	*map;
	t_player		*player;
	t_minimap		*minimap;
	t_raycasting	*raycasting;
}				t_structs;

//parsing

//initializing
void	init_values(t_structs *structs);

//graphical_part
void	create_image(t_mlx *mlx, t_image *image);
int		press_key(int key, t_structs *structs);
int		exit_program(t_structs *structs);
void	display_window(void); //t_maps_coord *map

//drawing_part
void	draw_in_image(t_structs *structs);
void	my_img_pixel_put(t_image *image, int x, int y, int color);

//draw_line_algorithm
//void	bhm_line(t_image *image, t_points *pt, int color);

//raycasting
void	clear_image(t_image *image);
void	draw_player(t_image *image, t_player *player, t_raycasting *raycasting);
void	draw_map2d(t_image *image, t_minimap *minimap);
void	draw_walls2d(t_image *image, t_minimap *minimap, int x, int y);
void	raycasting_algo(t_image *image, t_raycasting *raycasting);
void	draw_vertival_lines(t_image *image, t_raycasting *raycasting, int x);

//movements
void	move_player(int key, t_structs *structs);
void	translate_player(int key, t_structs *structs);
void	rotate_camera(int key, t_structs *structs);

//utils
size_t	ft_tablen(char **tab);
void	ft_error(void);

//free
void	free_tab_c(char **tab);
void	free_tab_i(int **tab, int size);

#endif
