/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:21:25 by cesasanc          #+#    #+#             */
/*   Updated: 2024/10/23 14:59:02 by cesasanc         ###   ########.fr       */
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

# define HEIGHT 1920
# define WIDTH 1920
# define ITER 69
# define FRAME_WAIT 5
# define PI 3.14159265358979323846
# define FOV 1.04719755119659774615
# define NUM_RAYS 100
# define TILE_SIZE 64

typedef struct s_img
{
	int		x;
	int		y;
	double	x0;
	double	y0;
}				t_img;

typedef struct s_cords
{
	double	min;
	double	max;
}				t_cords;

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

typedef struct s_texture
{
	mlx_image_t		*image;
	u_int32_t		*data;
	int				width;
	int				height;
	mlx_texture_t	*texture;
}				t_texture;

typedef struct s_player
{
	mlx_texture_t	*mini_p;
	mlx_image_t		*mini_player;
	double			angle;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	bool			moved;
	int				move_x;
	int				move_y;
	int				rotate;
}				t_player;

typedef struct t_ray
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_x;
	double		delta_dist_y;
	double		perp_wall_dist;
	int			step_x;
	int			step_y;
	int			side;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		step;
	double		tex_pos;
}				t_ray;

typedef struct s_data
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
	t_ray			ray;
	t_texture		texture[4];
	u_int32_t		iter;
	t_cords			x;
	t_cords			y;
	u_int32_t		palette[ITER];
	t_color			color;
	t_renderer		renderer;
	t_zoom			zoom;
	t_mouse			mouse;
	int				floor_color[3];
	int				ceiling_color[3];
	int				floor_rgba;
	int				ceiling_rgba;
	int				player_pos[2];
	char			**map;
	int				map_height;
	int				map_width;
	mlx_image_t		*map_floor;
	mlx_image_t		*map_wall;
}	t_data;

/* Utils */

void	print_error(char *str);
void	clean_exit(t_data *data, int status);
void	error_exit(t_data *data, char *str, int status);
int		get_rgba(int r, int g, int b, int a);

/* Initialization*/

t_data	*handle_args(int argc, char **argv, t_data *info);
int		ft_altoi(const char *str, int len);
int		ft_get_floor_color(t_data *info, char *f_color);
int		ft_get_ceiling_color(t_data *info, char *c_color);

/* Wall Textures */
int		ft_get_north_texture(t_data *info, char *line);
int		ft_get_south_texture(t_data *info, char *line);
int		ft_get_west_texture(t_data *info, char *line);
int		ft_get_east_texture(t_data *info, char *line);
void	init_textures(t_data *data);

int		ft_parsing_error(char *message);
int		ft_parse_scene_description(t_data *info, char *file);
int		ft_get_map_str(int fd, char **map_str);
int		ft_parse_map(t_data *info, int fd, char **line);
void	ft_find_player(t_data *info);
int		ft_is_player(char c);
int		ft_is_valid_content(char c);
int		ft_flood_fill(t_data *info, int x, int y);
void	ft_free_data(t_data **info);
void	ft_free_array(char **arr);

void	init_color_palette(t_data *win);
void	get_layout(t_data *win);
void	win_init(t_data *win);

int		ft_draw_minimap(t_data *data);
int		ft_draw_player_to_minimap(t_data *data);
void	ft_move_player(t_data *data, double dir_y, double dir_x);
void	ft_rotate_player(t_data *data, char direction);


/* Rendering */

void	render(void *param);
void	ft_draw_ray(t_data *data, int color);
void	draw_ceiling_and_floor(t_data *data);

/* Raycasting */

void	raycast(t_data *data, int x);
void	init_ray(t_data *data, int x);
void	set_dda(t_data *data);
void	perform_dda(t_data *data);
void	calc_wall(t_data *data);

/* Hooks */

void	key_hook(mlx_key_data_t key_data, void *param);
void	close_program(void *param);
void	ft_move_hook(void *param);
void	cursor_hook(double xpos, double ypos, void *param);

#endif