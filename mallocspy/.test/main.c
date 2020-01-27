/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abaur <abaur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 13:55:03 by abaur             #+#    #+#             */
/*   Updated: 2020/01/27 12:55:22 by abaur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mallocspy.h"

#include <stdio.h>

int main(void)
{
	void* p;
	unsigned long ul;
	short b;
	void* mallocs[64];

	printf("\n\tSpyReg :\n");
	for(int i=0; i<64; i++)
	{
		p = spyreg((void*)(unsigned long)i);
		if(p != (void*)(unsigned long)i)
			printf("[%d] Got %p.\n", i, p);
	}

	printf("\n\tSpyLog :\n");
	ul = (int)spylog();
	if (ul != 63)
		printf("Expected 63, got %lu.\n", ul);

	printf("\n\tSpyUnreg :\n");
	for(int i=0; i<32; i++)
	{
		b = spyunreg((void*)(unsigned long)i);
		if (!b)
			printf("[%d] Got %d", i, b);
	}

	printf("\n\tSpyLog :\n");
	ul = (int)spylog();
	if (ul != 32)
		printf("Expected 32, got %d.\n", (int)ul);

	printf("\n\tSpyReg duplicates : \n");
	for (int i=32; i<64; i++)
	{
		p = spyreg((void*)(unsigned long)i);
		if (p != (void*)(unsigned long)i)
				printf("[%d] Got : %p.\n", i, p);
	}

	printf("\n\tSpyUnreg duplicates :\n");
	for(int i=0; i<32; i++)
	{
		b = spyunreg((void*)(unsigned long)i);
		if (b)
			printf("[%d] Got %d\n", i, b);
	}

	printf("\n\tSpyLog :\n");
	ul = (int)spylog();
	if (ul != 32)
		printf("Expected 32, got %d.\n", (int)ul);

	printf("\n\tSpyUnreg :\n");
	for(int i=32; i<64; i++)
	{
		b = spyunreg((void*)(unsigned long)i);
		if (!b)
			printf("[%d] Got %d\n", i, b);
	}

	printf("\n\tSpyMalloc : \n");
	for (int i=0; i<64; i++)
	{
		mallocs[i] = spymalloc(8);
		if (mallocs[i] == NULL)
			printf("[%d] Returned NULL\n", i);
	}

	printf("\n\tSpyLog :\n");
	ul = (int)spylog();
	if (ul != 64)
		printf("Expected 64, got %d.\n", (int)ul);

	printf("\n\tSpyFree : \n");
	for (int i=0; i<32; i++)
	{
		spyfree(mallocs[i]);
	}

	printf("\n\tSpyLog :\n");
	ul = (int)spylog();
	if (ul != 32)
		printf("Expected 32, got %d.\n", (int)ul);

	printf("\n\tSpyFlush : \n");
	ul = spyflush();
	if (ul != 32)
		printf("Expected 32, got %lu.", ul);

	printf("\n\tSpyLog :\n");
	ul = (int)spylog();
	if (ul != 0)
		printf("Expected 0, got %d.\n", (int)ul);
}
