/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snakajim <snakajim@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/08 01:28:24 by snakajim          #+#    #+#             */
/*   Updated: 2024/05/08 01:44:04 by snakajim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_ele;

	if (lst == NULL || f == NULL)
		return (NULL);
	new_lst = NULL;
	while (lst)
	{
		new_ele = ft_lstnew(f(lst->content));
		if (new_ele == NULL)
		{
			if (del)
				ft_lstclear(&new_lst, del);
			return (new_lst);
		}
		ft_lstadd_back(&new_lst, new_ele);
		lst = lst->next;
	}
	return (new_lst);
}
