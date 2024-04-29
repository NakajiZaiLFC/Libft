/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/28 22:48:35 by snakajim          #+#    #+#             */
/*   Updated: 2024/04/29 05:35:59 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (count < n)
	{
		*((char *)s + count) = i;
		count++;
	}
	return (*s);
}
