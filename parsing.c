/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:20:31 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/07 15:20:32 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_parsing_error(char *message)
{
	write(2, "Error\ninvalid scene description\n", 32);
	if (message)
	{
		ft_putstr_fd(message, 2);
		write(2, "\n", 1);
	}
	return (1);
}

int	ft_get_elements(t_data *info, char *line, int *elements)
{
	if ((!ft_strncmp(line, "F ", 2) && \
		!ft_get_floor_color(info, line + 1)) || \
		(!ft_strncmp(line, "C ", 2) && \
		!ft_get_ceiling_color(info, line + 1)) || \
		(!ft_strncmp(line, "NO ", 3) && \
		!ft_get_north_texture(info, line + 2)) || \
		(!ft_strncmp(line, "SO ", 3) && \
		!ft_get_south_texture(info, line + 2)) || \
		(!ft_strncmp(line, "EA ", 3) && \
		!ft_get_east_texture(info, line + 2)) || \
		(!ft_strncmp(line, "WE ", 3) && \
		!ft_get_west_texture(info, line + 2)))
	{
		*elements += 1;
		return (0);
	}
	*elements = -1;
	return (1);
}

int	ft_parse_colors_and_textures(t_data *info, int fd)
{
	char	*line;
	int		elements;

	elements = 0;
	line = get_next_line(fd);
	while (line && (!ft_strncmp(line, "F ", 2) || !ft_strncmp(line, "C ", 2) \
			|| !ft_strncmp(line, "NO ", 3) || !ft_strncmp(line, "SO ", 3) || \
			!ft_strncmp(line, "WE ", 3) || !ft_strncmp(line, "EA ", 3) || \
			line[0] == '\n'))
	{
		if (line[0] != '\n' && ft_get_elements(info, line, &elements))
			break ;
		free(line);
		line = get_next_line(fd);
	}
	if (line && elements != -1 && elements != 6)
		ft_parsing_error("(textures/colors first, then a map)");
	else if (!line && elements != 6)
		ft_parsing_error("missing info (textures, colors, and a map needed)");
	if (elements == 6 && !ft_parse_map(info, fd, &line))
		return (0);
	if (line)
		free(line);
	return (1);
}

int	ft_parse_scene_description(t_data *info, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		ft_free_data(&info);
		write(2, "Error opening scene description file\n", 37);
		return (1);
	}
	if (ft_parse_colors_and_textures(info, fd))
	{
		ft_free_data(&info);
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}
