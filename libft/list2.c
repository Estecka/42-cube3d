/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:50:18 by abaur             #+#    #+#             */
/*   Updated: 2019/11/14 17:17:43 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

/*
** Frees the memory allocated to the element
** and deletes its content with the given method.
*/

void	ft_lstdelone(t_list *lst, void (*del)(void*))
{
	if (!lst)
		return ;
	if (del)
		del(lst->content);
	free(lst);
}

/*
** Frees the memory allocated to the given element and all the following,
** and deletes their content with the given method.
** Sets lst to null.
*/

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*next;

	if (!lst)
		return ;
	while (*lst)
	{
		next = (*lst)->next;
		if (del)
			del((*lst)->content);
		free(*lst);
		*lst = next;
	}
	*lst = NULL;
}

/*
** Executes f on each element's content.
*/

void	ft_lstiter(t_list *lst, void (*f)(void*))
{
	if (!f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
}

/*
** Executes f on each element's content to create a new list.
** Del will be used to clear the result in case an issue arises.
*/

t_list	*ft_lstmap(t_list *lst, void *(*f)(void*), void (*del)(void*))
{
	t_list	*result;
	t_list	*dst;

	if (!lst || !f)
		return (NULL);
	result = ft_lstnew(NULL);
	if (!result)
		return (NULL);
	result->content = f(lst->content);
	dst = result;
	while (lst->next)
	{
		dst->next = ft_lstnew(NULL);
		if (!dst->next)
		{
			ft_lstclear(&result, del);
			return (NULL);
		}
		dst->next->content = f(lst->next->content);
		dst = dst->next;
		lst = lst->next;
	}
	return (result);
}
