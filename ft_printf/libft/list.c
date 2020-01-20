/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student42.fr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 16:48:50 by abaur             #+#    #+#             */
/*   Updated: 2019/11/14 17:13:37 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
** Allocates a new list element.
*/

t_list	*ft_lstnew(void *content)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	if (!result)
		return (NULL);
	result->content = content;
	result->next = NULL;
	return (result);
}

/*
** Returns the size of the list.
*/

int		ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 1;
	while ((lst = lst->next))
		i++;
	return (i);
}

/*
** Returns the last element of the list.
*/

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/*
** Adds the given element at the beginning of the list.
** Returns the first element of the list through `alst`.
*/

void	ft_lstadd_front(t_list **alst, t_list *new)
{
	if (!alst || !new)
		return ;
	new->next = *alst;
	(*alst = new);
}

/*
** Adds the given element at the end of the list.
** Returns the first element of the list through `alst`.
*/

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*cursor;

	if (!alst)
		return ;
	if (!*alst)
		return (void)(*alst = new);
	cursor = *alst;
	while (cursor->next)
		cursor = cursor->next;
	cursor->next = new;
}
