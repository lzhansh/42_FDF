/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 20:32:22 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 09:24:54 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static t_coord	*start_pop(t_coord **c_list)
{
	t_coord *top;

	top = NULL;
	if (c_list && *c_list)
	{
		top = *c_list;
		*c_list = (*c_list)->next;
	}
	return (top);
}

/*
** Save z and color as 1D array in map struct.
*/

void			start_fdf(t_coord **c_list, t_map *map)
{
	t_coord *new;
	ssize_t	i;
	size_t	size;

	size = map->width * map->height * sizeof(int);
	if (!(map->coor = (int *)ft_memalloc(size)))
		error_msg(ERR_CONV);
	if (!(map->col = (int *)ft_memalloc(size)))
		error_msg(ERR_CONV);
	i = map->width * map->height - 1;
	while ((new = start_pop(c_list)) && i >= 0)
	{
		map->coor[i] = new->z;
		map->col[i] = new->color;
		if (new->z > map->z_max)
			map->z_max = new->z;
		if (new->z < map->z_min)
			map->z_min = new->z;
		i--;
		free(new);
	}
	map->z_range = map->z_max - map->z_min;
}

void			error_msg(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

int				close_win(void *p)
{
	(void)p;
	exit(0);
}
