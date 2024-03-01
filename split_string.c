#include "main.h"

/**
 * countWords - Counts the number of words in a string
 * @input: Input string
 * @delimiter: String of delimiters
 *
 * Return: Number of words
 */
static int countWords(const char *input, const char *delimiter)
{
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
	return (numWords);
}

/**
 * allocateMemory - Allocates memory for the array of strings
 * @numWords: Number of words
 *
 * Return: Pointer to the allocated memory
 */
static char **allocateMemory(int numWords)
{
	char **result = (char **)malloc((numWords + 1) * sizeof(char *))

	if (result == NULL)
		return (NULL);
	return (result);
}
/**
 * exWords - Extracts words from input str & stores them in end arr
 * @input: Input string
 * @delimiter: String of delimiters
 * @result: Array to store the extracted words
 */
static void exWords(const char *input, const char *delimiter, char **result)
{
	int resultSize = 0;
	const char *ptr = input;

	while (*ptr != '\0')
	{
		while (*ptr != '\0' && isDelimiter(*ptr, delimiter))
			ptr++;
		int wordLen = 0;
		const char *wordStart = ptr;

		while (*ptr != '\0' && !isDelimiter(*ptr, delimiter))
		{
			ptr++;
			wordLen++;
		}
		result[resultSize] = (char *)malloc(wordLen + 1);
		if (result[resultSize] == NULL)
		{
			for (int i = 0; i < resultSize; i++)
				free(result[i]);
			free(result);
			return;
		}
		for (int i = 0; i < wordLen; i++)
		{
			result[resultSize][i] = wordStart[i];
		}
		result[resultSize][wordLen] = '\0';
		resultSize++;
	}
	result[resultSize] = NULL;
}

/**
 * splitString - Splits a string into words based on a delimiter
 * @input: Input string to be split
 * @delimiter: String of delimiters to determine word boundaries
 *
 * Return: Pointer to array of strings containing the words or NULL on failure
 */
char **splitString(const char *input, const char *delimiter)
{
	if (input == NULL)
		return (NULL);
	if (delimiter == NULL)
		delimiter = " ";

	int numWords = countWords(input, delimiter);

	if (numWords == 0)
		return (NULL);
	char **result = allocateMemory(numWords);

	if (result == NULL)
		return (NULL);
	extractWords(input, delimiter, result);
	return (result);
}
