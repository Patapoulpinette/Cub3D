/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:05:01 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/07 12:01:37 by dbouron          ###   ########lyon.fr   */
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
# define PINK 0xfb6f92
# define YELLOW 0xe9c46a

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
	int		tile_size;
	int		wall_height;
	int		angle60;
	int		angle30;
	int		angle15;
	int		angle90;
	int		angle180;
	int		angle270;
	int		angle360;
	int		angle0;
	int		angle5;
	int		angle10;
	int		angle45;
	double	*sin_table;
	double	*sin_table_inv;
	double	*cos_table;
	double	*cos_table_inv;
	double	*tan_table;
	double	*tan_table_inv;
	double	*fish_table;
	double	*step_x_table;
	double	*step_y_table;
	int		proj_plane_y_center;
	int		map_x;
	int		map_y;
}				t_raycasting;

typedef struct s_player
{
	int		x;
	int		y;
	int		x_dir;
	int		y_dir;
	double	angle;
	int		dist_from_proj_plane;
	int		height;
	int		speed;
}				t_player;

typedef struct s_minimap
{
	int		map_xlen;
	int		map_ylen;
	char	**map;
	int		wall_size;
}				t_minimap;

typedef struct s_points
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_points;

typedef struct s_structs
{
	t_mlx			*mlx;
	t_image			*image;
	//t_maps_coord	*map;
	t_player		*player;
	t_minimap		*minimap;
	t_raycasting	*ray;
}				t_structs;

//parsing

//initializing
void	init_values(t_structs *structs);
void	fill_tables(t_structs *structs);
int		calculate_map_len_max(t_minimap *minimap);
void	print_array(double *array, int len);
void	init_tables(t_raycasting *ray);

//graphical_part
void	create_image(t_mlx *mlx, t_image *image);
int		press_key(int key, t_structs *structs);
int		exit_program(t_structs *structs);
void	display_window(void); //t_maps_coord *map

//drawing_part
void	draw_in_image(t_structs *structs);
void	my_img_pixel_put(t_image *image, int x, int y, int color);
double	degtorad(double angle, t_raycasting *ray);
void	draw_fill_rect(t_image *image, int x, int y, int height, int width, int color);

//draw_line_algorithm
void	bhm_line(t_image *image, t_points *pt, int color);

//raycasting
void	clear_image(t_image *image);
void	draw_map2d(t_image *image, t_minimap *minimap, t_player *player, t_raycasting *ray);
void	draw_ray_on_map2d(t_image *image, t_minimap *minimap, t_raycasting *ray, int x, int y);
void	draw_player_on_map2d(t_image *image, t_player *player, t_raycasting *ray);
void	raycast(t_image *image, t_minimap *minimap, t_player *player, t_raycasting *ray);
void	draw_walls(t_image *image, int cast_column, int top_wall, int bottom_wall);

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
