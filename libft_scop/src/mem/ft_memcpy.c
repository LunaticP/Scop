/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/01 01:38:25 by vthomas           #+#    #+#             */
/*   Updated: 2016/10/27 16:07:52 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			index;
	unsigned char	*tmp;

	index = 0;
	tmp = (unsigned char *)ft_strdup(src);
	while (index != n)
	{
		((unsigned char *)dst)[index] = tmp[index];
		index++;
	}
	free(tmp);
	return (dst);
}
