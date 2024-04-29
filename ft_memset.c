/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 21:55:47 by snakajim          #+#    #+#             */
/*   Updated: 2024/04/29 05:35:49 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
void *ft_memset(void *b, int c,size_t n)
{
	size_t count;

	count = 0;
		while(count < n)
		{
			*((char *)b+count) = c;
			count++;
		}
	return b;
}
