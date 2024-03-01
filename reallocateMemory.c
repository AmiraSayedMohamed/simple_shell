#include "main.h"

/**
 * reallocateMemory - Reallocates a block of memory
 * @ptr: Pointer to the previosly allocated block
 * @prevSize: Byte size of previous block
 * @newSize: Byte size of the new block
 *
 * Return: Pointer to the newly allocated block
 */
void *reallocateMemory(void *ptr, unsigned int prevSize, unsigned int newSize)
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
 * fillMemory - Fills a memory area with a constant byte
 * @ptr: Pointer to the memory area to be filled
 * @byte: Constant byte to fill the memory with
 * @numBytes: Number of bytes to be filled
 *
 * Return: A pointer to the filled memory area (same as ptr)
 */
void *fillMemory(void *ptr, unsigned char byte, unsigned int numBytes)
{
	unsigned char *bytePtr = (unsigned char *)ptr;

	for (unsigned int i = 0; i < numBytes; i++)
	{
		bytePtr[i] = byte;
	}

	return (ptr);
}

/**
 * freeStringArray - a function that frees the memory allocated for an array
 * @array: pointer to the array of strings
 *
 * Return: nothing
 */
void freeStringArray(char **array)
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
 * freeAndNull - frees a pointer and sets it to NULL
 * @ptr: Address of the pointer to free
 *
 * Return: (1) if freed successfully, (0) otherwise
 */

int freeAndNull(void **ptr)
{
	if (ptr == NULL || *ptr == NULL)
	{
		return (0);
	}

	free(*ptr);
	*ptr = NULL;

	return (1);
}

