/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_creation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 18:32:45 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/26 16:49:01 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_xpm_load(t_data *data)
{
	if (!data->textures.collectibles)
		exit_error(1, data);
	if (!data->textures.floor)
		exit_error(1, data);
	if (!data->textures.player)
		exit_error(1, data);
	if (!data->textures.exit)
		exit_error(1, data);
	if (!data->textures.wall)
		exit_error(1, data);
}

void	load_xpm_files(t_data *data)
{
	int	width;
	int	height;

	data->textures.wall = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/wall.xpm", &width, &height);
	data->textures.collectibles = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/collectibles.xpm", &width, &height);
	data->textures.exit = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/portal.xpm", &width, &height);
	data->textures.player = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/player.xpm", &width, &height);
	data->textures.floor = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/floor.xpm", &width, &height);

	check_xpm_load(data);
	// PENSER A FAIRE UNE FONCTION POUR CHECK SI XPM BIEN LOAD.
}

void	create_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->textures.wall, j * SPRITE_SIZE, i * SPRITE_SIZE);
			else if (data->map[i][j] == 'C')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->textures.collectibles, j * SPRITE_SIZE, i * SPRITE_SIZE);
			else if (data->map[i][j] == '0')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->textures.floor, j * SPRITE_SIZE, i * SPRITE_SIZE);
			else if (data->map[i][j] == 'E')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->textures.exit, j * SPRITE_SIZE, i * SPRITE_SIZE);
			else if (data->map[i][j] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->textures.player, j * SPRITE_SIZE, i * SPRITE_SIZE);
			j++;
		}
		i++;
	}
}
