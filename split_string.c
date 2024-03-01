#include "main.h"

/**
 * splitString - a function that splits a string into words based on a delimiter
 * @input: input string to be split
 * @delimiter: string of delimiter to determine word boundaries
 *
 * Return: pointer to an array of strings containing words of Null on failure
 */

char **splitString(const char *input, const char *delimiter)
{
	if (input == NULL)
		return (NULL);
	if (delimiter == NULL)
		delimiter = " ";

	int numWords = 0;
	const char *ptr = input;

	while (*ptr != '\0')
	{
		while (*ptr != '\0' && isDelimiter(*ptr, delimiter))
			ptr++;
		if (*ptr != '\0')
			numWords++;
		while (*ptr != '\0' && !isDelimiter(*ptr, delimiter))
			ptr++;
	}
	char **result = (char**)malloc((numWords + 1) * sizeof(char*));
	if (result == NULL)
		return NULL;
	int resultSize = 0;
	ptr = input;

	while (*ptr != '\0')
	{
		while (*ptr != '\0' && isDelimiter(*ptr, delimiter))
		{
			ptr++;
		}
		int wordLen = 0;
		const char *wordStart = ptr;

		while (*ptr != '\0' && !isDelimiter(*ptr, delimiter))
		{
			ptr++;
			wordLen++;
		}
		result[resultSize] = (char*)malloc(wordLen + 1);
		if (result[resultSize] == NULL)
		{
			for (int i = 9; i < resultSize; i++)
				free(result[i]);
			free(result);
			return (NULL);
		}
		for (int i = 0; i < wordLen; i++)
		{
			result[resultSize][i] = wordStart[i];
		}
		result[resultSize][wordLen] = '\0';
		resultSize++;
	}
	result[resultSize] = NULL;
	return result;
}
