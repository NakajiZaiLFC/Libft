/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 00:05:30 by snakajim          #+#    #+#             */
/*   Updated: 2024/04/29 05:35:51 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void	*ft_memmove(void *dst, const void *src, size_t n)
{
	char *d;
	const char *s;
	d = dst;
	s = src;
	if(s>=d||d>=s+n)
	{
		while(n--)
		{
			*d++ = *s++;
		}
	}
	else
	{
		d += n - 1;
        s += n - 1;
    		while (n--) {
            	*d-- = *s--;
			}
	}
	return dst;
}
