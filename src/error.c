/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:12:19 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/26 16:59:12 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	destroy_all_xpm_images(t_data *data)
{
	if (data->textures.collectibles)
		mlx_destroy_image(data->mlx_ptr, data->textures.collectibles);
	if (data->textures.floor)
		mlx_destroy_image(data->mlx_ptr, data->textures.floor);
	if (data->textures.player)
		mlx_destroy_image(data->mlx_ptr, data->textures.player);
	if (data->textures.exit)
		mlx_destroy_image(data->mlx_ptr, data->textures.exit);
	if (data->textures.wall)
		mlx_destroy_image(data->mlx_ptr, data->textures.wall);
}

void	free_strs(t_data *data)
{
	int	i;

	i = 0;
	while (data->map[i])
	{
		free(data->map[i]);
		i++;
	}
	free(data->map);
}

int	msg(char *str1, int exit_code)
{
	ft_putendl_fd(str1, 1);
	return (exit_code);
}

void	exit_error(int exit_code, t_data *data)
{
	if (data->mlx_window)
		mlx_destroy_window(data->mlx_ptr, data->mlx_window);
	destroy_all_xpm_images(data);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	if (data->map)
		free_strs(data);
	exit(exit_code);
}
