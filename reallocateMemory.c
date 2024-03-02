#include "main.h"

/**
 * _realloc - Reallocates a block of memory
 * @ptr: Pointer to the previosly allocated block
 * @prevSize: Byte size of previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the newly allocated block
 */
void *_realloc(void *ptr, unsigned int prevSize, unsigned int newSize)
{
	void *newPtr;

	newPtr = malloc(newSize);

	if (newPtr == NULL)
	{
		return (NULL);
	}
	char *oldCharPtr = (char *)ptr;
	char *newCharPtr = (char *)newPtr;

	unsigned int copySize = (prevSize < newSize) ? prevSize : newSize;

	for (unsigned int i = 0; i < copySize; i++)
	{
		newCharPtr[i] = oldCharPtr[i];
	}

	free(ptr);

	return (newPtr);
}

/**
 * _memset - Fills a memory area with a constant byte
 * @ptr: Pointer to the memory area to be filled
 * @byte: Constant byte to fill the memory with
 * @numBytes: Number of bytes to be filled
 *
 * Return: A pointer to the filled memory area (same as ptr)
 */
void *_memset(void *ptr, unsigned char byte, unsigned int numBytes)
{
	unsigned char *bytePtr = (unsigned char *)ptr;

	for (unsigned int i = 0; i < numBytes; i++)
	{
		bytePtr[i] = byte;
	}

	return (ptr);
}

/**
 * ffree - a function that frees the memory allocated for an array
 * @array: pointer to the array of strings
 *
 * Return: nothing
 */
void ffree(char **array)
{
	if (array != NULL)
	{
		for (int i = 0; array[i] != NULL; i++)
		{
			free(array[i]);
		}
		free(array);
	}
}

/**
 * bfree - frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: (1) if freed successfully, (0) otherwise
 */

int bfree(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
	{
		return (0);
	}

	free(*ptr);
	*ptr = NULL;

	return (1);
}

