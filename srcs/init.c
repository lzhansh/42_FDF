/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 16:04:40 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 10:38:51 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	*init_map(void)
{
	t_map *map;

	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		error_msg(ERR_INIT);
	map->width = 0;
	map->height = 0;
	map->coor = NULL;
	map->col = NULL;
	map->z_min = INT_MAX;
	map->z_max = INT_MIN;
	map->z_range = 0;
	return (map);
}

t_fdf	*init_fdf(t_map *map)
{
	t_fdf *fdf;

	if (!(fdf = (t_fdf *)ft_memalloc(sizeof(t_fdf))))
		error_msg(ERR_INIT);
	if (!(fdf->mlx = mlx_init()))
		error_msg(ERR_INIT);
	if (!(fdf->win = mlx_new_window(fdf->mlx, WIN_WID, WIN_HEI, "Lyako's FDF")))
		error_msg(ERR_INIT);
	if (!(fdf->img = mlx_new_image(fdf->mlx, WIN_WID, WIN_HEI)))
		error_msg(ERR_INIT);
	fdf->addr = mlx_get_data_addr(fdf->img, &(fdf->bpp),
	&(fdf->size_line), &(fdf->endian));
	fdf->map = map;
	if (!(fdf->mouse = (t_mouse *)ft_memalloc(sizeof(t_mouse))))
		error_msg(ERR_INIT);
	return (fdf);
}

t_cam	*init_cam(t_fdf *fdf)
{
	t_cam *cam;

	if (!(cam = (t_cam *)ft_memalloc(sizeof(t_cam))))
		error_msg(ERR_INIT);
	cam->zoom = FT_MIN((WIN_WID - MENU_WID) / fdf->map->width / 1.5,
	WIN_HEI / fdf->map->height / 1.5);
	cam->alpha = 0;
	cam->beta = 0;
	cam->gamma = 0;
	cam->z_div = 3;
	cam->x_off = 0;
	cam->y_off = -250;
	return (cam);
}
