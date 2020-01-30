/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lzhansha <lzhansha@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/02 14:58:12 by lzhansha          #+#    #+#             */
/*   Updated: 2019/07/12 10:35:41 by lzhansha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void			fdf_free(char **c)
{
	size_t i;

	i = 0;
	while (c[i])
		free(c[i++]);
	free(c);
}

/*
** Add new node into c_stack linked list
*/

static t_coord	*fdf_add_coord(char *s)
{
	t_coord	*new;
	char	**data;

	if (!(new = (t_coord *)ft_memalloc(sizeof(t_coord))))
		error_msg(ERR_MAP);
	if (!(data = ft_strsplit(s, ',')))
		error_msg(ERR_MAP);
	if (!ft_isdigit(data[0][0]))
		error_msg(ERR_MAP);
	new->z = ft_atoi(data[0]);
	new->color = data[1] ? ft_atoi_base(data[1] + 2, 16) : -1;
	new->next = NULL;
	fdf_free(data);
	return (new);
}

/*
** Save the coordinates from line into c_list as a linked list
*/

static void		fdf_parse(char **coords, t_map *map, t_coord **c_list)
{
	int		wid;
	t_coord	*new;

	wid = 0;
	while (*coords)
	{
		if (c_list)
		{
			if ((new = fdf_add_coord(*(coords++))))
				new->next = *c_list;
			*c_list = new;
		}
		wid++;
	}
	if (map->height == 0)
		map->width = wid;
	else if (map->width != wid)
		error_msg(ERR_MAP);
}

/*
** Read the file line by line using get_next_line
*/

static int		fdf_read(int fd, t_map *map, t_coord **c_list)
{
	char	*line;
	char	**coords;
	int		res;

	while ((res = get_next_line(fd, &line)) == 1)
	{
		if (!(coords = ft_strsplit(line, ' ')))
			error_msg(ERR_NODATA);
		fdf_parse(coords, map, c_list);
		fdf_free(coords);
		ft_strdel(&line);
		map->height++;
	}
	if (!(*c_list))
		error_msg(ERR_MAP);
	return (res);
}

int				main(int ac, char **av)
{
	int		fd;
	t_map	*map;
	t_coord *c_list;
	t_fdf	*fdf;

	errno = 0;
	c_list = NULL;
	if (ac != 2)
		error_msg(ERR_USAGE);
	if ((fd = open(av[1], O_RDONLY)) < 0)
		error_msg(ERR_NOFILE);
	map = init_map();
	if ((fdf_read(fd, map, &c_list)) == -1)
		error_msg(ERR_NODATA);
	fdf = init_fdf(map);
	start_fdf(&c_list, map);
	fdf->cam = init_cam(fdf);
	draw_fdf(fdf->map, fdf);
	control(fdf);
	mlx_loop(fdf->mlx);
	return (0);
}
