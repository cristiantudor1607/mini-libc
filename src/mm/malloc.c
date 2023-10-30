// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>


void *malloc(size_t size)
{
	if  (size == 0)
		return NULL;

	// Map the required chunk of memory using mmap
	void *chunk = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
	if (chunk == MAP_FAILED)
		return NULL;

	// Add the new chunk in the list
	// TODO: check if fail
	int ret = mem_list_add(chunk, size);
	
	return chunk;
}

void *calloc(size_t nmemb, size_t size)
{
	// Get a new chunk of memory
	void *mem_chunk = malloc(nmemb * size);
	if (mem_chunk == NULL)
		return NULL;

	// Set all the bytes to 0
	for (size_t i = 0; i < nmemb * size; i++)
		*((char *) mem_chunk + i) = 0;
	
	return mem_chunk;
}

void free(void *ptr)
{
	// If ptr is NULL, do nothing
	if (!ptr)
		return;

	// Find the chunk of memory that is about to be deleted
	struct mem_list *chunk = mem_list_find(ptr);
	if (!chunk)
		return;

	size_t size = chunk->len;
	
	// munmap shouldn't fail, because the ptr was already verified;
	// If the chunk pointed by ptr failed mapping, or it wasn't allocated by
	// malloc, it wouldn't have been added in the list and found by
	// mem_list_find function
	munmap(ptr, size);
	mem_list_del(ptr);
	
	// Don't forget to set the ptr to NULL :)
	ptr = NULL;
}

void *realloc(void *ptr, size_t size)
{	
	// If ptr is NULL, then is the same as malloc(size)
	if (!ptr)
		return malloc(size);

	// If the size is 0, then is the same as free(ptr)
	if (!size) {
		free(ptr);
		return NULL;
	}

	// Get the old size of the chunk
	struct mem_list *chunk = mem_list_find(ptr);
	if (!chunk)
		return NULL;

	size_t old_size = chunk->len;
	return mremap(ptr, old_size, size, MREMAP_MAYMOVE);
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	// As the manual page says, the reallocarray call is equivalent to
	// realloc(ptr, nmemb * size)
	return realloc(ptr, nmemb * size);
}
