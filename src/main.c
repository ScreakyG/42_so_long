/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:55:36 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/24 18:59:31 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(int *)pixel = color;
}

int	render_rectangle(t_img *img, t_rect rect)
{
	int	i;
	int	j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, RED_PXL);
		i++;
	}
	return (0);
}

int	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WINDOW_HEIGHT)
	{
		j = 0;
		while (j < WINDOW_WIDTH)
			img_pix_put(img, j++, i, color);
		i++;
	}
	return (0);
}

static int	render2(t_data *data)
{
	void	*wall;
	int		height;
	int		witdh;

	wall = mlx_xpm_file_to_image(data->mlx_ptr, "./textures/wall.xpm", &witdh, &height);
	if (data->mlx_window)
	{
		render_background(&data->img, WHITE_PXL);
		render_rectangle(&data->img, (t_rect){0, 0, 50, 50, RED_PXL});
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, data->img.mlx_img, 0, 0);
		mlx_put_image_to_window(data->mlx_ptr, data->mlx_window, wall, 100, 150);

	}
	return (0);
}

int	handle_keyPress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->mlx_window);
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
		data->mlx_window = NULL;
	}
	printf("Key Pressed : %d", keysym);
	return (0);
}

int	main(void)
{
	t_data	data;

	if (!(data.mlx_ptr = mlx_init()))
		return (MLX_ERR);
	if (!(data.mlx_window = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "Hello World")))
	{
		free(data.mlx_window);
		return (MLX_ERR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp, &data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.mlx_window, KeyPress, KeyPressMask, &handle_keyPress, &data);

	mlx_loop(data.mlx_ptr);

	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
