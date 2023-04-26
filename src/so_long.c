/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 21:08:17 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/26 17:04:28 by fgonzale         ###   ########.fr       */
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
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_window);
		destroy_all_xpm_images(data);
		data->mlx_window = NULL; // Pour que la fonction render stop.
	}
	printf("Key Pressed : %d", keysym);
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
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc != 2)
		return (printf("Only need .ber map as arg\n"), 1);
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
	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	free_strs(&data);
	return (0);
}
