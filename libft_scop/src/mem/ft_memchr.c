/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/12/16 13:27:36 by vthomas           #+#    #+#             */
/*   Updated: 2016/10/27 16:06:09 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			index;
	unsigned char	*tmp_s;

	tmp_s = (unsigned char *)ft_strdup(s);
	index = 0;
	while (index < n)
	{
		if (tmp_s[index] == (unsigned char)c)
		{
			free(tmp_s);
			return (tmp_s + index);
		}
		index++;
	}
	free(tmp_s);
	return (0);
}
