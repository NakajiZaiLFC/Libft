/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 21:03:31 by snakajim          #+#    #+#             */
/*   Updated: 2024/05/11 01:18:49 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

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

char	*ft_strchr(const char *s, int c)
{
	unsigned char	chr;
	size_t			i;

	chr = (unsigned char)c;
	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == chr)
			return ((char *)&s[i]);
		i++;
	}
	if (chr == '\0')
		return ((char *)&s[i]);
	return (NULL);
}

// int	main(void)
// {
// 	const char	*s = "Hello World";
// 	char		c;

// 	c = '\0';
// 	printf("%s\n", strchr(s, c));
// 	printf("%s\n", ft_strchr(s, c));
// 	return (0);
// }
