/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nvallin <nvallin@student.hive.fi>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 16:59:55 by nvallin           #+#    #+#             */
/*   Updated: 2024/10/07 17:09:47 by nvallin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

int	ft_get_map(t_data *info, char *map_str)
{
	int	i;

	i = 0;
	info->map = malloc((info->map_height + 1) * sizeof(char *));
	if (!info->map)
	{
		perror("ft_get_map");
		return (1);
	}
	while (i < info->map_height)
	{
		printf("%s\n",  map_str + gnl_strchr_index(map_str, '\n'));
		info->map[i] = gnl_strldup(map_str, gnl_strchr_index(map_str, '\n'));
		if (!info->map[i])
		{
			perror("ft_get_map");
			return (1);
		}
		map_str = map_str + gnl_strchr_index(map_str, '\n');
		i++;
	}
	info->map[i] = NULL;
	return (0);
}

int	ft_check_map_end(char *map_str)
{
	while (*map_str == '\n')
		map_str++;
	if (*map_str == '\0')
		return (0);
	if (*map_str != '0' && *map_str != '1' && *map_str != 'N' && \
		*map_str != 'S' && *map_str != 'E' && *map_str != 'W' && \
		*map_str != ' ')
		ft_parsing_error("map has to be the last element in file");
	else
		ft_parsing_error("map can't be seperated by newline");
	return (1);
}

int	ft_check_map_content(t_data *info, char *map_str)
{
	int	width;

	width = 0;
	while (*map_str)
	{	
		if (*map_str != '0' && *map_str != '1' && *map_str != 'N' && \
			*map_str != 'S' && *map_str != 'E' && *map_str != 'W' && \
			*map_str != ' ' && *map_str != '\n' && \
			ft_parsing_error("invalid map content"))
			return (1);
		if (*map_str == '\n')
		{
			info->map_height++;
			if (width > info->map_width)
				info->map_width = width;
			width = -1;
			if (*(map_str + 1) == '\n')
				break ;
		}
		width++;
		map_str++;
	}
	if (ft_check_map_end(map_str))
		return (1);
	return (0);
}

int	ft_get_map_str(int fd, char **map_str)
{
	char	*line;

	line = get_next_line(fd);
	while (line)
	{
		*map_str = gnl_strjoin(*map_str, line);
		free(line);
		if (!*map_str)
		{
			perror("ft_parse_map");
			return (1);
		}
		line = get_next_line(fd);
	}
	if (!*map_str)
	{
		ft_parsing_error("missing map");
		return (1);
	}
	return (0);
}

int	ft_parse_map(t_data *info, int fd, char **line)
{
	char	*map_str;

	map_str = ft_strdup(*line);
	free(*line);
	*line = NULL;
	if (!map_str)
	{
		perror("ft_parse_map");
		return (1);
	}
	if (ft_get_map_str(fd, &map_str) || ft_check_map_content(info, map_str) \
		|| ft_get_map(info, map_str))
	{
		if (map_str)
			free(map_str);
		return (1);
	}
	free(map_str);
	return (0);
}
