/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apercebo <apercebo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:33:54 by dbouron           #+#    #+#             */
/*   Updated: 2022/10/17 14:28:26 by apercebo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

#define mapWidth 24
#define mapHeight 24
#define screenWidth 640
#define screenHeight 480

int worldMap[mapWidth][mapHeight]=
{
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

/* void	display_window(void)
{
	t_image			image;
	t_raycasting	ray;
	t_structs		structs;

	structs.mlx = &mlx;
	structs.image = &image;
	structs.ray = &ray;
	init_raycasting_values(&ray);
	create_image(&mlx, &image);
	draw_in_image(&mlx, &image, &ray);
} */

void	screen(int sWidth, int sHeight, t_mlx *mlx, char *str)
{
	mlx->mlx_ptr = mlx_init();
	mlx->win_ptr = mlx_new_window(mlx->mlx_ptr, sWidth, sHeight, str);
}

int main(int argc, char *argv[])
{
	t_mlx	mlx;
	int		x;
	char	**y;

	algo(&mlx);
	/* mlx_hook(mlx.window, 02, 0L, press_key, &structs);
	mlx_hook(mlx.window, 17, 1L << 5, exit_program, &structs); */
	mlx_loop(mlx.mlx_ptr);
}

int	algo(t_mlx *mlx)
{
	double posX = 22, posY = 12;  //Position du joueur (X et Y)
	double dirX = -1, dirY = 0; //Vecteur de direction (ex: dir x=1 signifie que le joueur regarde vers le haut de la carte)
	double planeX = 0, planeY = 0.66; //Position du Camera plane (A droite ou a gauche de [pos + dir] ) {on peut le changer pour changer le FOV (ici fov=66degrès)}

 	double time = 0; //Temps de l'image actuel (Permet de calculer les fps en regardant le temps entre 2 images)
 	double oldTime = 0; //Temps de l'image précedente
	double	w = screenWidth; //w = largeur de l'écran

	screen(screenWidth, screenHeight, &mlx, "Raycaster");
	while(!done())
  	{
		for(int x = 0; x < w; x++)
    	{
    		//calculate ray position and direction
    		double cameraX = 2 * x / w - 1; //Position de X sur le camera plane
    		double rayDirX = dirX + planeX * cameraX; //Direction X du rayon
    		double rayDirY = dirY + planeY * cameraX; //Direction Y du rayon
			//which box of the map we're in
    		int mapX = posX; //X coordonné du carré de la map dans lequel on est situé
    		int mapY = posY; //Y coordonné du carré de la map dans lequel on est situé

    		//length of ray from current position to next x or y-side
    		double sideDistX; //Distance initial que le rayon a à parcourir avant d'atteindre le prochain carré en X
    		double sideDistY; //Distance initial que le rayon a à parcourir avant d'atteindre le prochain carré en Y

    		 //length of ray from one x or y-side to next x or y-side
    		double deltaDistX = (rayDirX == 0) ? 1e30 : std::abs(1 / rayDirX); //Distance parcouru pour joindre les 2 cotés X d'un bloc
    		double deltaDistY = (rayDirY == 0) ? 1e30 : std::abs(1 / rayDirY); //Distance parcouru pour joindre les 2 cotés Y d'un bloc
    		double perpWallDist; // Utile pour calculer la longueur du rayon (et donc la distance entre le joueur et le mur)

    		//what direction to step in x or y-direction (either +1 or -1)
    		int stepX; //La direction dans lequel est le prochain mur (1 = on va à droite, -1 = on va à gauche)
    		int stepY; //La direction dans lequel est le prochain mur (1 = on monte, -1 = on descend)

    		int hit = 0; //Detecte si on a rencontré un mur
    		int side; //Determine de quel coté un mur a été toucher (0 = gauche/droite | 1 = haut/bas)

			//calculate step and initial sideDist
			if (rayDirX < 0)
			{
				stepX = -1;
				sideDistX = (posX - mapX) * deltaDistX; //Calcule la distance entre le joueur et le mur
			}
			else
			{
				stepX = 1;
				sideDistX = (mapX + 1.0 - posX) * deltaDistX; //Calcule la distance entre le joueur et le mur
			}
			if (rayDirY < 0)
			{
				stepY = -1;
				sideDistY = (posY - mapY) * deltaDistY; //Calcule la distance entre le joueur et le mur
			}
			else
			{
				stepY = 1;
				sideDistY = (mapY + 1.0 - posY) * deltaDistY; //Calcule la distance entre le joueur et le mur
			}
			//perform DDA
			while (hit == 0)
			{
				//jump to next map square, either in x-direction, or in y-direction
				if (sideDistX < sideDistY)
				{
					sideDistX += deltaDistX;
					mapX += stepX;
					side = 0;
				}
				else
				{
					sideDistY += deltaDistY;
					mapY += stepY;
					side = 1;
				}
				//Check if ray has hit a wall
				if (worldMap[mapX][mapY] > 0) hit = 1;
    		}
		}
	}
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

void	parsing(t_data *data, char **argv)
{
	name_error(argv[1]);
	count_line(data, argv[1]);
	backtracking(data);
	debug(data);
	free_tab_c(data->game_map);
	free_tab_c(data->f_game_map);
	free(data->no_path);
	free(data->so_path);
	free(data->we_path);
	free(data->ea_path);
}

/* int	main(int argc, char **argv)
{
	t_data			data;

	if (argc != 2)
		return (0);
	parsing(&data, argv);
	return (0);
} */

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
}
