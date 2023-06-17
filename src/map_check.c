/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: parallels <parallels@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/21 22:35:27 by fgonzale          #+#    #+#             */
/*   Updated: 2023/06/14 10:34:04 by parallels        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_map_paths(t_data *data)
{
	int	collectibles;
	int	exit;
	char **map_copy;

	collectibles = data->textures.collectibles_nb;
	exit = 1;
	map_copy = strs_strdup(data->map, data);
	if (!map_copy)
		printf("Map copy error"); // CHANGER
	// PARCOURIR LA MAP
		// DES QUE ON TOMBE SUR C OU E , envoyer la position de C/E et faire une fonction récursive pour comparer la position de C par 
		//rapport à la player_pos
	while (*map_copy)
	{
		printf("%s\n", *map_copy);
		map_copy++;
	}
	if (collectibles != 0 || exit != 0)
		exit_error(msg("Collectible or exit might not be accessible", 1), data);
}

char **strs_strdup(char **strs, t_data *data)
{
	char **copy;
	int	i;

	i = 0;
	copy = malloc((data->map_height + 1) * sizeof(char *));
	if (!copy)
		return (NULL);
	while (i < data->map_height)
	{
		copy[i] = ft_strdup2(strs[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

static void	check_map_char(t_data *data)
{
	int	i;
	int	j;
	int	exit;
	int	player;

	data->textures.collectibles_nb = 0;
	exit = 0;
	player = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'C')
				data->textures.collectibles_nb++;
			else if (data->map[i][j] == 'E')
				exit++;
			else if (data->map[i][j] == 'P')
				player++;
			else if (data->map[i][j] != '0' && data->map[i][j] != '1')
				exit_error(msg("Wrong map values", 1), data);
			j++;
		}
		i++;
	}
	if (data->textures.collectibles_nb == 0 || exit != 1 || player != 1)
		exit_error(msg("Error with map items", 1), data);
}

static void	check_map(t_data *data, unsigned int height)
{
	unsigned int	i;
	unsigned int	j;
	unsigned int	width;

	i = 0;
	if (!data->map[i] || data->map[i][0] == '\0') // Moyennement correct
		exit_error(msg("File empty\n", 1), data);
	width = ft_strlen(data->map[i]);
	data->map_width = width;
	while (data->map[i])
	{
		if (ft_strlen(data->map[i]) != width)
			exit_error(msg("Map not rectangle", 1), data);
		j = 0;
		while (data->map[i][j])
		{
			if (i == 0 && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
			if (j == 0 && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
			if (j == (width - 1) && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
			if (i == ((height - 1)) && data->map[i][j] != '1')
				exit_error(msg("Map not closed", 1), data);
			j++;

		}
		i++;
	}
	check_map_char(data);
}

static int	number_lines(char *map_arg, t_data *data)
{
	int		fd_map;
	int		count;
	char	*line;

	fd_map = open(map_arg, O_RDONLY);
	if (fd_map == -1)
		exit_error(msg(strerror(errno), 1), data);
	count = 0;
	line = get_next_line(fd_map);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd_map);
	}
	close(fd_map);
	return (count);

}

void	check_map_is_valid(t_data *data, char *map_arg)
{
	int		fd_map;
	char	*line;
	int		i;

	i = 0;
	fd_map = open(map_arg, O_RDONLY);
	if (fd_map == -1)
		exit_error(msg(strerror(errno), 1), data);
	data->map = malloc((number_lines(map_arg, data) + 1) * sizeof(char *));
	if (!data->map)
	{
		close(fd_map);
		exit_error(msg("Malloc map error", 1), data);
	}
	line = get_next_line(fd_map);
	while (line)
	{
		data->map[i] = ft_strtrim(line, "\n");
		free(line);
		i++;
		line = get_next_line(fd_map);
	}
	data->map[i] = NULL;
	data->map_height = i;
	close(fd_map);
	check_map(data, data->map_height);
	check_map_paths(data);
}

void	check_map_format(char **argv, t_data *data)
{
	int	i;

	i = 0;
	if (ft_strlen(argv[1]) <= 4)
		exit_error(msg("Map format is not correct", 1), data);
	while (argv[1][i])
		i++;
	i -= 4;
	if (!ft_strncmp(".ber", &argv[1][i], 4))
		return ;
	else
		exit_error(msg("Map format must be .ber", 1), data);
}
