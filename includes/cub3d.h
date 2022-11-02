/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dbouron <dbouron@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:05:01 by dbouron           #+#    #+#             */
/*   Updated: 2022/11/02 17:58:27 by dbouron          ###   ########lyon.fr   */
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
//# include <time.h>
# include <string.h>

# define RESOLUTION_X 5120 //on iMac (Retina 5K, 27-inch, 2017)
# define RESOLUTION_Y 2880 //on iMac (Retina 5K, 27-inch, 2017)
# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480

//# define FLOOR_COLOR 0xdda15e
# define WALL_COLOR 0x606c38
//# define SKY_COLOR 0xbde0fe
# define PINK 0xfb6f92
# define YELLOW 0xe9c46a
# define BLACK 0xFFFFFF

# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define DOWN_ARROW 125
# define UP_ARROW 126
# define ESC 53

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
	int		save;
	int		map_end;
	char	pl_orientation;
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
	int		orientation;
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
}				t_mouse;

typedef struct s_points
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_points;

typedef struct s_structs
{
	t_data			*data;
	t_mlx			*mlx;
	t_image			*image;
	t_texture		*texture;
	t_raycasting	*ray;
	t_player		*player;
	t_minimap		*minimap;
	t_mouse			*mouse;
}				t_structs;

//initializing
void	init_raycasting_values(t_structs *structs);
void	set_player_orientation_ne(t_structs *structs);
void	set_player_orientation_sw(t_structs *structs);
int		calculate_map_len_max(char **map);
int		create_trgb(int t, int r, int g, int b);

//texture
void	draw_textures(t_image *image, t_player *player, t_raycasting *ray, t_texture *texture, int x);
void	choose_orientation(t_raycasting *ray, t_texture *texture);
void	calculate_wall_x(t_player *player, t_raycasting *ray, t_texture *texture);
void	calculate_x_coordinate_on_texture(t_raycasting *ray, t_texture *texture);
int		get_texture_pixel(t_texture texture, int x, int y);

//graphical_part
void	create_image(t_mlx *mlx, t_image *image);
void	load_textures(t_mlx *mlx, t_texture *texture);
int 	move_mouse(int x, int y, t_structs *structs);
int		press_key(int key, t_structs *structs);
int		exit_program(t_structs *structs);
void	link_structs(t_mlx *mlx, t_image *image, t_structs *structs);
void	display_window(t_data *data);

//drawing_part
void	draw_in_image(t_structs *structs);
void	clear_image(t_image *image);
void	draw_map2d(t_image *image, t_raycasting *ray, t_minimap *minimap);
void	draw_map2d_rays(t_image *image, t_player *player, t_minimap *minimap, int x, int y);
void	draw_map2d_player(t_image *image, t_player *player, t_minimap *minimap);
void	draw_fill_rect(t_image *image, int x, int y, int height, int width);
void	my_img_pixel_put(t_image *image, int x, int y, int color);

//draw_line_algorithm
void	bhm_line(t_image *image, t_points *pt, int color);

//raycasting
void	raycasting_algo(t_image *image, t_player *player, t_raycasting *ray, t_minimap *minimap, t_texture *texture);
void	calculate_step_and_side_dist(t_player *player, t_raycasting *ray);
void	perform_dda(t_image *image, t_player *player, t_raycasting *ray, t_minimap *minimap);
void	calculate_walls(t_raycasting *ray);
void	draw_vertival_lines(t_image *image, t_raycasting *raycasting, int x);

//movements
void	move_player(int key, t_structs *structs);
void	translate_player(int key, t_structs *structs);
void	rotate_camera_left(t_structs *structs, double rot_speed);
void	rotate_camera_right(t_structs *structs, double rot_speed);


//---- MAIN ------------------------------------
void	debug(t_data *data);
void	name_error(char *maplink);
void	get_data_info(t_data *data);
void	count_line(t_data *data, char *maplink);
void	recup_map(t_data *data, int fd, int i, char *maplink);
void	parsing(t_data *data, char **argv);
//----------------------------------------------

//---- PARSING ---------------------------------
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
//----------------------------------------------

//---- BACKTRACKING ----------------------------
void	backtracking(t_data *data);
int		ch_is_player(int j);
void	check_path(t_data *data, int i, int j);
void	delete_walls(t_data *data);
int		ch_is_in_map(t_data *data, int i, int j);
int		ch_is_a_corner(t_data *data, int i, int j);
void	display(t_data *data);
//----------------------------------------------

//---- UTILS -----------------------------------
int		ft_atoi(const char *str);
int		search_ch(t_data *data, int j);
int		search_ch_in_map(int j);
int		ch_is_inside(int j);
size_t	ft_tablen(char **tab);
void	ft_error(void);
void	free_tab_c(char **tab);
void	free_tab_i(int **tab, int size);
//----------------------------------------------

#endif
