/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mansargs <mansargs@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 20:30:54 by mansargs          #+#    #+#             */
/*   Updated: 2025/06/21 18:19:08 by mansargs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*map;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	map = NULL;
	while (lst)
	{
		content = f(lst->content);
		if (!content)
			return (NULL);
		new = ft_lstnew(content);
		if (!new)
		{
			ft_lstclear(&map, del);
			free(content);
			return (NULL);
		}
		ft_lstadd_back(&map, new);
		lst = lst->next;
	}
	return (map);
}
