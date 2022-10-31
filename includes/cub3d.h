/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:05:01 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/31 15:59:35 by apercebo         ###   ########.fr       */
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
# include <time.h>
# include <string.h>

typedef struct s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_mlx;

typedef struct s_text
{
	void	*img_ptr;
	char	*addr;
	char	*path;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
}				t_text;

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

//---- MAIN ------------------------------------
void	debug(t_data *data);
void	name_error(char *maplink);
void	get_data_info(t_data *data);
void	count_line(t_data *data, char *maplink);
void	recup_map(t_data *data, int fd, int i, char *maplink);
void	parsing(t_data *data, char **argv);
void	free_tab_c(char **tab);
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
