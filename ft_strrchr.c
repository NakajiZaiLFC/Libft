/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 00:53:56 by snakajim          #+#    #+#             */
/*   Updated: 2024/05/11 01:20:59 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// size_t	ft_strlen(const char *s)
// {
// 	size_t	len;

// 	len = 0;
// 	while (s[len] != '\0')
// 	{
// 		len++;
// 	}
// 	return (len);
// }

char	*ft_strrchr(const char *s, int c)
{
	unsigned char	chr;
	size_t			i;
	size_t			len;

	chr = (unsigned char)c;
	i = 0;
	len = ft_strlen(s);
	if (chr == '\0')
		return ((char *)&s[len]);
	while (len > 0)
	{
		if (s[len - 1] == chr)
			return ((char *)&s[len - 1]);
		len--;
	}
	return (NULL);
}
