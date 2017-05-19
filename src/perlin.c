/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   perlin.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aviau <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/15 12:57:35 by aviau             #+#    #+#             */
/*   Updated: 2017/05/15 15:57:14 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/time.h>
#include "libft.h"

unsigned char	*gen_image(int xx, int yy)
{
	unsigned char	*image;
	struct timeval	time;
	int				x;
	int				y;

	gettimeofday(&time, NULL);
	srandom((time.tv_sec + time.tv_usec) / 2);
	image = (unsigned char *)ft_memalloc(xx * yy);
	y = -1;
	while (++y < yy && (x = -1))
		while (++x < xx)
			image[y * xx + x] = (random() % 32768) / 32768.0 * 255.0;
	return (image);
}

float			smooth(float x, float y, int m, unsigned char *map)
{
	float	fctx;
	float	fcty;
	int		fstx;
	int		fsty;
	int		sndx;
	int		sndy;
	float		value;

	fctx = x - (int)x;
	fcty = y - (int)y;
	value = 0.0;
	fstx = (int)x % m;
	fsty = (int)y % m;
	sndx = ((int)x + m - 1) % m;
	sndy = ((int)y + m - 1) % m;
	value += fctx * fcty * (map[fsty * m + fstx] / 255.0);
	value += (1.0 - fctx) * fcty * (map[fsty * m + sndx] / 255.0);
	value += fctx * (1.0 - fcty) * (map[sndy * m + fstx] / 255.0);
	value += (1.0 - fctx) * (1.0 - fcty) * (map[sndy * m + sndx] / 255.0);
	return (value);
}

int				merge(unsigned char **images, int x, int y)
{
	float	div;
	float	val;
	int		i;

	i = 0;
	div = 1.0;
	val = (int)(smooth(x, y, 2048, images[0]) * 255.0);
	while (++i < 7)
	{
		div *= 2.0;
		val += (smooth(x / div, y / div, 2048 / div, images[i]) * 255.0);
	}
	val /= 8.0;
	return ((int)val * 0x10000 + (int)val * 0x100 + (int)val);
}

int				*perlin(void)
{
	unsigned char	*img[8];
	int				*tex;
	int				x;
	int				y;

	tex = (int *)ft_memalloc(sizeof(int) * 2048 * 2048 + 3);
	tex[0] = 2048 * 2048 + 3;
	tex[1] = 2048;
	tex[2] = 2048;
	img[0] = gen_image(2048, 2048);
	img[1] = gen_image(1024, 1024);
	img[2] = gen_image(512, 512);
	img[3] = gen_image(256, 256);
	img[4] = gen_image(128, 128);
	img[5] = gen_image(64, 64);
	img[6] = gen_image(32, 32);
	img[7] = gen_image(16, 16);
	y = -1;
	while (++y < 2048)
	{
		x = -1;
		while (++x < 2048)
			tex[y * 2048 + x + 3] = merge((unsigned char **)img, x, y);
	}
	return (tex);
}
