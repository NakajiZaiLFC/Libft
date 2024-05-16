/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 01:04:58 by snakajim          #+#    #+#             */
/*   Updated: 2024/05/17 04:37:19 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count && size > SIZE_MAX / count)
		return (NULL);
	ptr = (void *)malloc(count * size);
	if (ptr == NULL || (count == 0 || size == 0))
		return (ptr);
	ft_bzero(ptr, (count * size));
	return (ptr);
}

// void	*ft_calloc(size_t nmemb, size_t size)
// {
// 	void	*array;

// 	if (nmemb && size > SIZE_MAX / nmemb)
// 		return (NULL);
// 	array = (void *)malloc(nmemb * size);
// 	if (array == NULL)
// 		return (NULL);
// 	ft_bzero(array, (nmemb * size));
// 	return (array);
// }

// void	ft_bzero(void *s, size_t n)
// {
// 	size_t	i;
// 	size_t	count;

// 	i = 0;
// 	count = 0;
// 	while (count < n)
// 	{
// 		*((char *)s + count) = i;
// 		count++;
// 	}
// 	return (*s);
// }

// int main(void)
// {
//     size_t count = (size_t)SIZE_MAX / 10 + (size_t)1;
//     size_t size = 10;
//     void *ptr = ft_calloc(count, size);
//     void *ptr2 = calloc(count, size);

//     if (ptr == NULL || ptr2 == NULL)
//     {
//         printf("Memory allocation failed\n");
//         return (1);
//     }

//     size_t allocated_size_ft_calloc = count * size;
//     size_t allocated_size_calloc = count * size;

//     if (allocated_size_ft_calloc != allocated_size_calloc)
//     {
//         printf("Different sizes of memory allocated\n");
//         return (1);
//     }

//     printf("Memory allocation successful\n");

//     free(ptr);
//     free(ptr2);

//     return (0);
// }
