/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocspy_internals.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/27 12:08:44 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mallocspy.h"

static void		**g_spylist = NULL;
static size_t	g_spycap = 0;

/*
** Initialize or expands the list of pointer.
** The size of the list is then doubled.
** @return bool
** 	true  Expansion succesful
** 	false Allocation failed
*/

static short	spyexpand(void)
{
	void	**newlist;
	size_t	newcap;
	size_t	i;

	newcap = g_spycap ? g_spycap * 2 : 32;
	if (!(newlist = malloc(newcap * sizeof(void*))))
		return (0);
	i = 0;
	if (g_spylist)
	{
		while (i < g_spycap)
		{
			newlist[i] = g_spylist[i];
			i++;
		}
		free(g_spylist);
	}
	while (i < newcap)
		newlist[i++] = NULL;
	g_spylist = newlist;
	g_spycap = newcap;
	return (1);
}

extern short	spyunreg(void *ptr)
{
	short	status;
	size_t	i;

	status = 0;
	i = 0;
	while (i < g_spycap)
	{
		if (g_spylist[i] == ptr)
		{
			g_spylist[i] = NULL;
			status = 1;
		}
		i++;
	}
	if (SPYVERBOSE && !status)
		ft_printf("Tried to unregister a pointer, \
but that pointer is unknown : %p\n", ptr);
	return (status);
}

/*
** @var short status
** 	1 << 0 The pointer is registered
** 	1 << 1 The pointer was already registered
*/

extern void		*spyreg(void *ptr)
{
	short	status;
	size_t	i;

	status = 0;
	i = -1;
	while (++i < g_spycap)
		if (g_spylist[i] == NULL && !(status & 1 << 0))
		{
			g_spylist[i] = ptr;
			status |= 1 << 0;
		}
		else if (g_spylist[i] == ptr)
		{
			if ((status & 1 << 0))
				g_spylist[i] = NULL;
			status |= 1 << 1 | 1 << 0;
		}
	if (!(status & 1 << 0) && !spyexpand())
		return (NULL);
	if (!(status & 1 << 0))
		g_spylist[i] = ptr;
	if (SPYVERBOSE && (status & 1 << 1))
		ft_printf("Tried to register the same pointer multiple times: \
%p\n", ptr);
	return (ptr);
}

extern size_t	spylog(void)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = -1;
	while (++i < g_spycap)
		if (g_spylist[i] != NULL)
		{
			ft_printf("%p\n", g_spylist[i]);
			count++;
		}
	ft_printf("\nUp to %u pointers were registered simultaneously.\n",
		(unsigned int)g_spycap);
	ft_printf("There are %u pointers still registered.\n", (unsigned int)count);
	return (count);
}

extern	size_t	spyflush(void)
{
	size_t	i;
	size_t	count;

	i = -1;
	count = 0;
	while (++i < g_spycap)
		if (g_spylist[i] != NULL)
		{
			free(g_spylist[i]);
			g_spylist[i] = NULL;
			count++;
		}
	return (count);
}
