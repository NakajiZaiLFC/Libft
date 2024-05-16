/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 04:21:37 by snakajim          #+#    #+#             */
/*   Updated: 2024/05/07 23:23:38 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// #include <stdio.h>
// #include <string.h>

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*p1 = s1;
	const unsigned char	*p2 = s2;

	while (n > 0)
	{
		if (*p1 != *p2)
		{
			return (*p1 - *p2);
		}
		p1++;
		p2++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
//     const char	*s1 = "Hello aaaWorld";
//     const char	*s2 = "Heaos df World";
//     size_t		n = 5;

//     printf("%d\n", memcmp(s1, s2, n));
//     printf("%d\n", ft_memcmp(s1, s2, n));
//     return (0);
// }