/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dfm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:41:51 by mbiliaie          #+#    #+#             */
/*   Updated: 2018/10/23 01:42:11 by mbiliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

short				set_default_vals(struct s_gen *base, char *j)
{
	short int		z;
	short int		out;

	z = 0;
	out = z;
	base->c.scale = 0.45;
	if (ft_strcmp(base->type, j) == z)
		base->c.t_i = 127;
	else
		base->c.t_i = 77;
	base->c.ctr = -0.72;
	base->c.t_x = z;
	base->c.cti = -0.26999;
	base->c.t_y = z;
	base->c.rgb = 200;
	base->c.base = base;
	return (out);
}

static short		inner_loop(struct s_frc	*w, struct s_disp *d,
	struct s_add *z, struct s_adjust *a)
{
	short int		k;

	k = 0;
	while (++a->start < a->fin && (z->x = z->tmp))
		while (++z->x < d->x_fract)
		{
			w->rtp = a->t_x + 1.499 * (z->x - d->x_tab * 0.5) /
			(a->scale * d->x_tab * 0.48);
			w->i = a->t_y + (a->start - d->y_tab * 0.5) /
			(a->scale * d->y_tab * 0.48);
			w->ntr = k;
			w->nti = k;
			z->i = k;
			while (z->i < a->t_i && (w->ntr * w->ntr + w->nti * w->nti) <= 4)
			{
				w->pto = w->ntr;
				w->pti = w->nti;
				w->ntr = w->pto * w->pto - w->pti * w->pti + w->rtp;
				w->nti = 2 * w->pto * w->pti + w->i;
				++z->i;
			}
			PIXELPUT;
		}
	return (k);
}

void				*mandelbrot(struct s_adjust *a)
{
	struct s_disp	d;
	struct s_add	q;
	struct s_frc	w;

	set_dimensions(&d);
	if (a)
	{
		set_dimensions(&d);
		q.tmp = -1;
		inner_loop(&w, &d, &q, a);
	}
	pthread_exit(NULL);
}

short int			run_mlx(struct s_gen *bs, char *title, struct s_disp *d)
{
	short int		x;

	x = 0;
	set_dimensions(d);
	if (!(bs->mlx = mlx_init()))
		x++;
	else if (!(bs->win = NEWIND(bs->mlx, d->x_tab, d->y_tab, title)))
		x++;
	else if (!(bs->img = mlx_new_image(bs->mlx, d->x_fract, d->y_fract)))
		x++;
	else if (!(bs->str = GETADR(bs->img, &bs->smt, &bs->size, &bs->fnsh)))
		x++;
	if (x > 0)
	{
		write(2, "ERROR! mlx initialisation has failed\n", 37);
		return (1);
	}
	return (0);
}
