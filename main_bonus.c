/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cesasanc <cesasanc@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 15:22:01 by nvallin           #+#    #+#             */
/*   Updated: 2024/11/07 12:26:12 by cesasanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Cub3d.h"

void	hooks_n_loops(t_data *data)
{
	mlx_key_hook(data->mlx, &key_hook, data);
	mlx_set_mouse_pos(data->mlx, WIDTH / 2, HEIGHT / 2);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_cursor_hook(data->mlx, &cursor_hook, data);
	mlx_close_hook(data->mlx, &close_program, data);
	mlx_loop_hook(data->mlx, &render, data);
	mlx_loop_hook(data->mlx, &ft_move_hook, (void *)data);
	mlx_loop_hook(data->mlx, &ft_shoot, (void *)data);
	mlx_loop(data->mlx);
}

int	ft_init_textures(t_data *data)
{
	if (ft_get_door_texture(data) || get_enemy_texture(data))
		return (1);
	data->map_wall = mlx_texture_to_image(data->mlx, data->east_texture);
	if (!data->map_wall || !mlx_resize_image(data->map_wall, 16, 16))
	{
		print_error("minimap wall");
		return (1);
	}
	data->map_frame = mlx_texture_to_image(data->mlx, data->north_texture);
	if (!data->map_frame || !mlx_resize_image(data->map_frame, 16, 16))
	{
		print_error("minimap frame");
		return (1);
	}
	if (load_frames(data))
		return (1);
	return (0);
}

void	init_game(t_program_data *prog_data, t_data *data)
{
	handle_args(prog_data->argc, prog_data->argv, data);
	win_init(data);
	if (mlx_image_to_window(data->mlx, data->img, 0, 0) == -1 || \
		ft_init_textures(data) || ft_draw_minimap_background(data) || \
		ft_draw_minimap_frame(data))
		clean_exit(data, 1);
	if (draw_minimap(data, 250, 250))
	{
		print_error("draw_minimap");
		clean_exit(data, 1);
	}
	if (ft_draw_player_to_minimap(data))
	{
		print_error("ft_draw_player_to_minimap");
		clean_exit(data, 1);
	}
	place_enemies(data);
}

int main(int argc, char **argv)
{
    t_data          *data;
    t_program_data  *prog_data;

    data = malloc(sizeof(t_data));
    if (!data)
        return (1);
    prog_data = malloc(sizeof(t_program_data));
    if (!prog_data)
    {
        free(data);
        return (1);
    }
    prog_data->data = data;
    prog_data->argc = argc;
    prog_data->argv = argv;
    data->prog_data = prog_data;
    init_game(prog_data, data);
    hooks_n_loops(data);
    mlx_terminate(data->mlx);
    free(prog_data);
    free(data);
    return (0);
}

