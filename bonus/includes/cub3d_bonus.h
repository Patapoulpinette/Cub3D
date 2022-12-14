/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:05:01 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/08 19:25:52 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "mlx.h"
# include "get_next_line.h"
# include "libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <string.h>

# define SCREEN_WIDTH 1280
# define SCREEN_HEIGHT 960
//# define SCREEN_WIDTH 640
//# define SCREEN_HEIGHT 480

# define WALL_COLOR 0x606c38
# define PINK 0xfb6f92
# define YELLOW 0xe9c46a
# define WHITE 0xFFFFFF
# define BLACK 0x000000

# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define DOWN_ARROW 125
# define UP_ARROW 126
# define ESC 53
# define PLUS 24
# define MINUS 27

typedef enum e_orientation
{
	north,
	east,
	south,
	west,
}			t_orientation;

typedef struct s_incr
{
	int		i;
	int		j;
	int		x;
	int		save;
}		t_incr;

typedef struct s_data
{
	char	**map;
	char	**game_map;
	char	**f_game_map;
	int		height;
	int		no;
	char	*no_path;
	int		so;
	char	*so_path;
	int		we;
	char	*we_path;
	int		ea;
	char	*ea_path;
	int		ftabl[3];  //colors
	int		ctabl[3];  //colors
	int		f; //floor
	int		c; //ceiling
	int		i;  //data->i pour tabl
	int		j;	//data->j pour tabl
	int		save_i;  //data->save_i pour tabl
	int		save;
	int		map_end;
	char	pl_orientation;
	int		pl_x;
	int		pl_y;
	char	*nbr;
	t_incr	inc;
}		t_data; //todo variable orientation joueur

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

typedef struct s_hud
{
	void	*img;
	int		height;
	int		width;
}				t_hud;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	char	*path;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
	int		width;
	int		height;
	int		orient;
	double	wall_x; //where exactly the wall was hit
	int		tex_x;
	int		tex_y;
}				t_texture;

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

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
}				t_player;

typedef struct s_raycasting
{
	char	**map;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	int		side; //was a NS or a EW wall hit?
	int		draw_start;
	int		draw_end;
	double	camera_x;
	double	ray_x;
	double	ray_y;
	int		map_x;
	int		map_y;
	double	side_dist_x; //length of ray from current position to next x-side
	double	side_dist_y; //length of ray from current position to next y-side
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x; //what direction to step in x-direction (either +1 or -1)
	int		step_y; //what direction to step in y-direction (either +1 or -1)
	int		hit;
	int		line_height;
	int		ceiling_color;
	int		floor_color;
}				t_raycasting;

typedef struct s_minimap
{
	int	map_xlen;
	int	map_ylen;
	int	wall_zoom;
}				t_minimap;

typedef struct s_mouse
{
	int	button_press;
	int	prev_mouse_x;
	int	save_x;
	int	save_y;
}				t_mouse;

typedef struct s_points
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_points;

typedef struct s_dimensions
{
	int	x;
	int	y;
	int	height;
	int	width;
}				t_dimensions;

typedef struct s_structs
{
	t_data			*data;
	t_mlx			*mlx;
	t_image			*image;
	t_hud			*hud;
	t_texture		*texture;
	t_raycasting	*ray;
	t_player		*player;
	t_minimap		*minimap;
	t_mouse			*mouse;
}				t_structs;

//---- MAIN --------------------------------------------------------------------
void	debug(t_data *data);
void	name_error(char *maplink);
void	get_data_info(t_data *data);
void	count_line(t_data *data, char *maplink);
void	recup_map(t_data *data, int fd, int i, char *maplink);
void	parsing(t_data *data, char **argv);

//---- PARSING -----------------------------------------------------------------
int		texturing(t_data *data);
void	texturing_init(t_data *data);
void	no_path(t_data *data);
void	so_path(t_data *data);
void	we_path(t_data *data);
void	ea_path(t_data *data);
void	f_color(t_data *data);
void	c_color(t_data *data);
int		map_parsing(t_data *data);
int		map_error(t_data *data);
int		skip_space(t_data *data);
void	malloc_map(t_data *data);
void	replace_dot(t_data *data);
void	color_free_exit(t_data *data);
void	data_checks(t_data *data);

//---- BACKTRACKING ------------------------------------------------------------
void	backtracking(t_data *data);
int		ch_is_player(int j);
void	check_path(t_data *data, int i, int j);
void	delete_walls(t_data *data);
int		ch_is_in_map(t_data *data, int i, int j);
int		ch_is_a_corner(t_data *data, int i, int j);
void	display(t_data *data);

//---- INITIALIZING ------------------------------------------------------------
void	init_raycasting_values(t_structs *structs);
void	set_player_orientation_ne(t_structs *structs);
void	set_player_orientation_sw(t_structs *structs);
int		calculate_map_len_max(char **map);
int		create_trgb(int t, int r, int g, int b);

//---- GRAPHICAL PART ----------------------------------------------------------
void	create_image(t_mlx *mlx, t_image *image);
void	load_textures(t_mlx *mlx, t_texture *texture);
void	link_structs(t_mlx *mlx, t_image *image, t_structs *structs);
void	display_window(t_data *data);

//---- DRAWING PART ------------------------------------------------------------
void	draw_in_image(t_structs *structs);
void	draw_map2d(t_image *image, t_raycasting *ray, t_minimap *minimap);
void	draw_map2d_rays(t_structs *structs, int x, int y);
void	draw_map2d_player(t_image *image, t_player *player, t_minimap *minimap);

//---- DRAWING UTILS -----------------------------------------------------------
void	my_img_pixel_put(t_image *image, int x, int y, int color);
void	clear_image(t_image *image);
void	draw_fill_rect(t_image *image, t_dimensions *dim, int color);
void	draw_vertival_lines(t_image *image, t_raycasting *raycasting, int x);

//--- DRAWLINE ALGO ------------------------------------------------------------
void	bhm_line(t_image *image, t_points *pt, int color);

//--- RAYCASTING ---------------------------------------------------------------
void	raycasting_algo(t_structs *structs);
void	start_algo(t_structs *structs, int x);
void	calculate_step_and_side_dist(t_player *player, t_raycasting *ray);
void	perform_dda(t_structs *structs);
void	calculate_walls(t_raycasting *ray);

//---- TEXTURE -----------------------------------------------------------------
void	draw_textures(t_structs *structs, int x);
void	choose_orientation(t_raycasting *ray, t_texture *texture);
void	calculate_wall_x(t_player *player, t_raycasting *ray, t_texture *texture);
void	calculate_x_coordinate_on_texture(t_raycasting *ray, t_texture *texture);
int		get_texture_pixel(t_texture texture, int x, int y);

//---- INPUTS ------------------------------------------------------------------
int		press_key(int key, t_structs *structs);
int		press_mouse(int key, int x, int y, t_structs *structs);
int		release_mouse(int key, int x, int y, t_structs *structs);
int		move_mouse(int x, int y, t_structs *structs);
int		exit_program(t_structs *structs);

//---- MOVEMENTS ---------------------------------------------------------------
void	move_player(int key, t_structs *structs);
void	translate_player(int key, t_structs *structs);
void	rotate_camera_left(t_structs *structs, double rot_speed);
void	rotate_camera_right(t_structs *structs, double rot_speed);

//---- UTILS -------------------------------------------------------------------
int		search_ch(t_data *data, int j);
int		search_ch_in_map(int j);
int		ch_is_inside(int j);
size_t	ft_tablen(char **tab);
void	ft_error(void);
void	free_tab_c(char **tab);
void	error_exit(void);

#endif
