/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 01:38:25 by vthomas           #+#    #+#             */
/*   Updated: 2016/10/27 16:05:20 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t			index;
	unsigned char	*dst_tmp;
	unsigned char	*src_tmp;

	index = 0;
	dst_tmp = (unsigned char *)dst;
	src_tmp = (unsigned char *)ft_strdup(src);
	while (index != n)
	{
		dst_tmp[index] = src_tmp[index];
		if (dst_tmp[index] == (unsigned char)c)
		{
			free(src_tmp);
			return ((void *)((unsigned long)dst + index + 1));
		}
		index++;
	}
	free(src_tmp);
	return (NULL);
}
