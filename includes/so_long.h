/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgonzale <fgonzale@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 18:53:49 by fgonzale          #+#    #+#             */
/*   Updated: 2023/04/26 16:23:21 by fgonzale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define SPRITE_SIZE 32
# define MLX_ERR 1

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include "fcntl.h"
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <stdio.h>
# include <X11/keysym.h>
# include <X11/X.h>

typedef struct s_text
{
	void	*wall;
	void	*floor;
	void	*player;
	void	*collectibles;
	void	*exit;
}	t_textures;

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_struct
{
	char		**map;
	int			map_width;
	int			map_height;
	void		*mlx_ptr;
	void		*mlx_window;
	t_textures textures;
}	t_data;

/* Map Check*/

void	check_map_format(char **argv, t_data *data);
void	check_map_is_valid(t_data *data, char *map_arg);

/* Map Creation */

void	create_map(t_data *data);
void	load_xpm_files(t_data *data);

/* Error */

int		msg(char *str1, int exit_code);
void	exit_error(int exit_code, t_data *data);
void	free_strs(t_data *data);
void	destroy_all_xpm_images(t_data *data);

//int	render_rectangle(t_img *img, t_rect rect);
int	render_background(t_img *img, int color);
void	img_pix_put(t_img *img, int x, int y, int color);

/* Input Handling */

int	render(t_data *data);
int	handle_keyPress(int keysym, t_data *data);

#endif
