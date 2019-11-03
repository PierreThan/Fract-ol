/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pthan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 02:51:58 by pthan             #+#    #+#             */
/*   Updated: 2019/10/25 02:51:59 by pthan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../includes/fdf.h"

int		free_map(t_fdf *fdf)
{
	int		i;

	i = 0;
	if (fdf && fdf->map)
	{
		while (i < fdf->height)
		{
			if (fdf->map[i])
				ft_memdel((void **)&(fdf->map[i++]));
		}
		free(fdf->map);
		fdf->map = NULL;
	}
	return (0);
}

int		main(int ac, char **argv)
{
	t_fdf	fdf;

	if (ac != 2)
	{
		ft_printf("usage error - use 1 and only 1 argument\n");
		return (0);
	}
	fdf.file = argv[1];
	if ((fdf.fd = open(fdf.file, O_RDONLY)) < 0)
	{
		ft_printf("usage error\n");
		return (0);
	}
	if (!parse_file(&fdf))
		return (free_map(&fdf));
	ft_display_window(&(fdf.mlx), fdf.file, WIN_WIDTH, WIN_HEIGHT);
	draw(&fdf);
	setup_controls(&fdf);
	mlx_loop(fdf.mlx.mlx_ptr);
	free_map(&fdf);
	return (0);
}
