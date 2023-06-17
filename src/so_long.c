/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:08:17 by fgonzale          #+#    #+#             */
/*   Updated: 2023/06/12 22:48:37 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	render(t_data *data)
{
	if (data->mlx_window)
	{
		create_map(data);
	}
}

int	handle_keyPress(int keysym, t_data *data)
{
	if (keysym == XK_Escape || keysym == DestroyNotify)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_window);
		destroy_all_xpm_images(data);
		data->mlx_window = NULL; // Pour que la fonction render stop.
	}
	else if (keysym == XK_w || keysym == XK_W)  // Touche W;
		move_player(0, -1, data);
	else if (keysym == XK_a || keysym == XK_A)
		move_player(-1, 0, data);
	else if (keysym == XK_s || keysym == XK_S)
		move_player(0, 1, data);
	else if (keysym == XK_d || keysym == XK_D)
		move_player(1, 0, data);
	//printf("Key Pressed : %d", keysym);
	return (0);
}

static void	init_data(t_data *data)
{
	data->map = NULL;
	data->mlx_ptr = NULL;
	data->mlx_window = NULL;
	data->textures.collectibles = NULL;
	data->textures.exit = NULL;
	data->textures.floor = NULL;
	data->textures.player = NULL;
	data->textures.wall = NULL;
	data->move_count = 0;
}

static int	cross_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	destroy_all_xpm_images(data);
	data->mlx_window = NULL;
	mlx_loop_end(data->mlx_ptr);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	free_strs(data);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Only need .ber map as arg\n"), 1); // CHANGER PAR MON PRINTF
	init_data(&data); // PERMET DE PAS AVOIR DE LEAK UNCONDITIONAL JUMP
	check_map_format(argv, &data);
	check_map_is_valid(&data, argv[1]);

	if (!(data.mlx_ptr = mlx_init()))
		exit_error(MLX_ERR, &data); // EXIT ERROR FREE LES MALLOCS
	if (!(data.mlx_window = mlx_new_window(data.mlx_ptr, SPRITE_SIZE * data.map_width, SPRITE_SIZE * data.map_height, "so_long")))
	{
		free(data.mlx_window);
		exit_error(MLX_ERR, &data); // EXIT ERROR FREE LES MALLOCS
	}
	load_xpm_files(&data); // EXIT ERROR SI LOAD FAIL

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.mlx_window, KeyPress, KeyPressMask, &handle_keyPress, &data);
	mlx_hook(data.mlx_window, DestroyNotify, ButtonPressMask, &cross_close, &data); // POUR FERMER AVEC LA CROIX
	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	free_strs(&data);
	return (0);
}
