/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:21:25 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/08 13:47:43 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "./libft/libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <math.h>
# include <stdlib.h>
# include <string.h>
# include "MLX42/include/MLX42/MLX42.h"

# define HEIGHT 800
# define WIDTH 800
# define ITER 69
# define FRAME_WAIT 5

typedef struct s_cords
{
	double	min;
	double	max;
}				t_cords;

typedef struct s_complex
{
	double	r;
	double	i;
}				t_complex;

typedef struct s_renderer
{
	int		frames;
	bool	changed;
}				t_renderer;

typedef struct s_color
{
	double		r_o;
	double		g_o;
	double		b_o;
}				t_color;

typedef struct s_zoom
{
	double	x;
	double	y;
	double	factor;
	double	level;
}				t_zoom;

typedef struct s_mouse
{
	int32_t	x;
	int32_t	y;
}				t_mouse;

typedef struct s_win
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	u_int32_t	iter;
	t_cords		x;
	t_cords		y;
	t_complex	complex;
	u_int32_t	palette[ITER];
	t_color		color;
	t_renderer	renderer;
	t_zoom		zoom;
	t_mouse		mouse;
}				t_win;

typedef struct s_data
{
	int				floor_color[3];
	int				ceiling_color[3];
	mlx_texture_t	*north_texture;
	mlx_texture_t	*south_texture;
	mlx_texture_t	*west_texture;
	mlx_texture_t	*east_texture;
	char			**map;
	int				map_height;
	int				map_width;
}	t_data;

int		ft_altoi(const char *str, int len);
int		ft_get_floor_color(t_data *info, char *f_color);
int		ft_get_ceiling_color(t_data *info, char *c_color);
int		ft_get_north_texture(t_data *info, char *line);
int		ft_get_south_texture(t_data *info, char *line);
int		ft_get_west_texture(t_data *info, char *line);
int		ft_get_east_texture(t_data *info, char *line);
int		ft_parsing_error(char *message);
int		ft_parse_scene_description(t_data *info, char *file);
int		ft_parse_map(t_data *info, int fd, char **line);
void	ft_free_data(t_data **info);
void	ft_free_array(char **arr);

#endif
