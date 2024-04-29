/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 05:40:07 by snakajim          #+#    #+#             */
/*   Updated: 2024/04/29 17:50:47 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
size_t	ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	i=0;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dstsize <= len_dst)
		return (dstsize + len_src);
	while (src[i] && len_dst + i < dstsize - 1)
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}
size_t ft_strlen(const char *s)
{
    size_t len;

    len = 0;
	if(s == NULL)
	{
		return 0;
	}
    while(s[len]!='\0')
    {
    len++;
    }
    return len;
}
