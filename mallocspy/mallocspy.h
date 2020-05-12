/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mallocspy.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 15:38:42 by abaur             #+#    #+#             */
/*   Updated: 2020/01/23 13:39:25 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOCSPY_H
# define MALLOCSPY_H

# include <stdlib.h>
# include "../ft_printf/ft_printf.h"

/*
** You may set these define to either 0 or 1 to change the behaviour of some fu
** nctions.
** `SPYVERBOSE` prints warning when invalid pointers are detected.
** `SPYBRAVE` causes invalid pointers to be processed like valid ones.
** `SPYPROXY` causes mallocspy to treat pointers as being "second degree" inste
** ad of first degree. In other words, you register the adress of a variable th
** at holds a pointer instead of the pointer itself.
** This operating mode is a little more complex to uses, but has a handful of a
** dvantages :
**  - Pointer in registered variables can be changed without interfacing with M
** allocspy; pointers that are freed then reallocated in-place won't need to be
**  manually unregistered and re-registered.
**  - Pointers that are freed then set to NULL without interfacing with Mallocs
** py can be automatically detected and unregistered in bulk using `SpyClean`.
** You must however make sure to unregister such variable before they are thems
** selves deallocated (heap) or fall out of scope (stack).
**  - Mallocspy will in most case, never end up obfuscating leaks from tools li
** ke Valgrind. (Unless the registered variable also happens to be an allocated
**  pointer itself.)
*/

# ifndef SPYVERBOSE
#  define SPYVERBOSE 1
# endif
# ifndef SPYBRAVE
#  define SPYBRAVE 0
# endif
# ifndef SPYPROXY
#  define SPYPROXY 1
# endif

# ifndef SPYPROXY

/*
** Allocates memory, and registers it internally.
** @param size_t size The amount of bytes to allocate.
** @return void* A pointer to the memory, or NULL if an error occured.
*/

void	*spymalloc(size_t size);

# endif

/*
** Frees a pointer that was registered using either `spymalloc` or `spyreg`.
**
** This safely ignores NULL pointers.
** `SPYVERBOSE` prints a warning if the pointer is not registered or NULL.
** `SPYBRAVE` attempts to free even such pointers.
** @param void** pointer
*/

void	spyfree(void **pointer);

/*
** Registers a pointer internally.
** You can use this on pointer that were created without using `spymalloc`.
** In the end, `spymalloc(size)` is short for `spyreg(malloc(size))`.
**
** This safely ignores NULL pointers.
** `SPYVERBOSE` prints a warning if the pointer is NULL or already registered.
** @param void* pointer The pointer to register
** @return void* The same pointer, or NULL if an error occured.
*/

void	*spyreg(void *pointer);

/*
** Unregisters a pointer internally.
** Use this on pointers that were registered, but freed without 'spyfree'.
** This has no effect if the pointer is not already registered.
** `SPYVERBOSE` prints a warning if the pointer is NULL or not registered.
** @param void* pointer The pointer to unregister
** @return bool
** 	true  The pointer was unregistered.
** 	false The pointer was not registered to begin with.
*/

short	spyunreg(void *pointer);

/*
** Prints all currently registered adresses.
** @return size_t The amount of registered pointers.
*/

size_t	spylog(void);

/*
** Frees and unregister all known pointers.
** This also frees Mallocspy's internal pointers. These are automatically initi
** alized, so it doesn't prevent Mallocspy from working.
** @return size_t The amount of pointers freed.
*/

size_t	spyflush(void);

# if SPYPROXY

/*
** Unregisters all variables that hold NULL pointers.
** @return size_t   The amount of unregistered variables.
*/

size_t	spyclean(void);

# endif

#endif
