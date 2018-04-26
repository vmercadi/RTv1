/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maintest2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmercadi <vmercadi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/16 20:00:54 by vmercadi          #+#    #+#             */
/*   Updated: 2018/04/24 20:01:02 by vmercadi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
** Main loop for raytracing
*/

void		render_aliasing(t_b *b, t_px ref)
{
	int			i;
	int			j;
	t_px		px;

	px = ref;
	i = -1;
	while (++i < b->aliasing)
	{
		px.x = ref.x + i;
		j = -1;
		while (++j < b->aliasing)
		{
			px.y = ref.y + j;
			if (px.y < b->winy && px.x < b->winx)
				b->tab_px[px.y][px.x] = px;
		}
	}
}

void		render(void *arg)
{
	t_b			*b;
	t_px		px;
	t_ray		ray;

	b = (t_b *)arg;
	b->colmax = 0.;
	px.x = 0;
	while (px.x < b->winx)
	{
		px.y = 0;
		while (px.y < b->winy)
		{
			ray = init_ray(b->cam.pos, dir_vp_pixel(b, px), b->max);
			px.dist = inter_obj(b, &ray);
			px.col = cast_ray(b, ray);
			px.id = b->inter.id;
			render_aliasing(b, px);
			px.y += b->aliasing;
		}
		px.x += b->aliasing;
	}
	draw_lux(b);
	draw(b);
	action(b->act);
}

/*
** Start the program
*/

void		start(t_b *b)
{
	init_b(b);
	init_win(b);
	if (b->ac == 2)
		parse_main(b, b->av);
	else if (b->ac < 2)
		scene(b);
	b->ui = UI_main();
	while (event(b))
	{
		render(b);
		SDL_UpdateWindowSurface(b->win);
		SDL_UpdateWindowSurface(b->ui.win);
		if (b->rec)
			ev_screenshot(b);
	}
	SDL_DestroyWindow(b->win);
	SDL_DestroyWindow(b->ui.win);
	SDL_StopTextInput();
	SDL_Quit();
}

int			main(int ac, char **av)
{
	t_b			b;

	if (ac == 2 && !ft_strcmp(av[1], "help"))
	{
		man_help();
		return (0);
	}

	b.ac = ac;
	b.av = av[1];
	b.rec = 0;
	start(&b);
	return (0);
}
