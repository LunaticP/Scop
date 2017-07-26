/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 02:12:52 by vthomas           #+#    #+#             */
/*   Updated: 2016/10/27 16:09:32 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;
	unsigned char	*tmp;

	if (n == 0)
		return (dst);
	if (dst > src)
	{
		tmp = (unsigned char *)ft_strdup(src);
		i = n - 1;
		while (i != 0)
		{
			((unsigned char *)dst)[i] = tmp[i];
			i--;
		}
		((unsigned char *)dst)[i] = tmp[i];
		free(tmp);
	}
	else
		ft_memcpy(dst, src, n);
	return (dst);
}
