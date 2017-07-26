/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vthomas <vthomas@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/08 13:22:48 by vthomas           #+#    #+#             */
/*   Updated: 2017/05/18 21:08:55 by aviau            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	*ft_memjoin(unsigned char *dst, unsigned char *src, int sdst, int ssrc)
{
	void *mem;

	mem = ft_memalloc(sizeof(unsigned char) * (ssrc + sdst));
	ft_memcpy(mem, dst, sdst);
	ft_memcpy(&mem[sdst], src, ssrc);
	ft_strdel((char **)&dst);
	return (mem);
}
