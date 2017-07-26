/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/27 22:39:53 by vthomas           #+#    #+#             */
/*   Updated: 2016/10/27 16:19:56 by vthomas          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	size_t index;

	index = 0;
	while (s[index] && s[index] != (char)c)
		index++;
	if (s[index] == c)
		return ((char *)s + index);
	return (0);
}
