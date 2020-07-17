/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dft.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbiliaie <mbiliaie@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/23 01:42:17 by mbiliaie          #+#    #+#             */
/*   Updated: 2018/10/23 01:42:21 by mbiliaie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fractol.h"

void				handle_exit(int inp, struct s_gen *base)
{
	struct s_keys	b;
	char			*exit_notification;

	set_buttons(&b);
	exit_notification = "Fract'ol exited successfully! See you soon!\n";
	while (b.escape == inp)
	{
		mlx_clear_window(base->mlx, base->win);
		mlx_destroy_image(base->mlx, base->img);
		mlx_destroy_window(base->mlx, base->win);
		write(1, exit_notification, ft_strlen(exit_notification));
		exit(0);
	}
}

static short		inner_loop(struct s_frc *w, struct s_disp *d,
	struct s_add *z, struct s_adjust *a)
{
	short int		k;

	k = 0;
	while (++a->start < a->fin && (z->x = z->tmp))
		while (d->x_fract > ++z->x)
		{
			w->rtp = a->t_x + 1.499 * (z->x - d->x_tab * 0.5) /
			(a->scale * d->x_tab * 0.48);
			w->i = a->t_y + (a->start - d->y_tab * 0.5) /
			(a->scale * d->y_tab * 0.48);
			w->nti = k;
			w->ntr = k;
			z->i = k;
			while (z->i < a->t_i && (w->ntr * w->ntr + w->nti * w->nti) <= 4)
			{
				w->pto = w->ntr;
				w->pti = w->nti;
				w->ntr = w->pto * w->pto - w->pti * w->pti + w->rtp;
				w->nti = w->pto * w->pti * z->tmp * 2 + w->i;
				++z->i;
			}
			PIXELPUT;
		}
	return (k);
}

void				*tricorn(struct s_adjust *a)
{
	struct s_frc	w;
	struct s_disp	d;
	struct s_add	z;

	if (a)
	{
		z.tmp = -1;
		set_dimensions(&d);
		inner_loop(&w, &d, &z, a);
	}
	pthread_exit(NULL);
}

short				pxput(struct s_gen *base, int x_coord, int y_coord, int rgb)
{
	short			k;
	int				n;
	int				p;
	struct s_disp	d;
	short int		s;

	s = 8;
	k = 0;
	set_dimensions(&d);
	if (x_coord >= d.x_fract)
		k++;
	else if (y_coord >= d.y_fract)
		k++;
	else if (x_coord < 0)
		k++;
	else if (y_coord < 0)
		k++;
	if (k != 0)
		return (k);
	n = base->size * y_coord;
	p = (base->smt / s) * x_coord;
	n += p;
	*(int *)&base->str[n] = rgb;
	return (k);
}
