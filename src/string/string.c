// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>
#define BUFF_SIZE 128

char *strcpy(char *destination, const char *source)
{
	size_t i = 0;
	/* Copy byte by byte until it reaches the NULL terminator */
	while (*(source + i) != '\0') {
		*(destination + i) = *(source + i);
		i++;
	}

	/* Put the NULL terminator */
	*(destination + i) = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t i = 0;
	/* Copy byte by byte, until it reaches the number of required bytes, or
	until the string ends */
	while (*(source + i) != '\0' && i < len) {
		*(destination + i) = *(source + i);
		i++;
	}

	/* Set the remaining bytes, if neccessary, to 0 */
	while (i < len) {
		*(destination + i) = '\0';
		i++;
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	/* Set a pointer to the end of the destination */
	size_t dest_len = strlen(destination);
	char *p = destination + dest_len;

	size_t i = 0;
	/* Copy all the bytes from source to p, moving pointer p */
	while (*(source + i) != '\0') {
		*(p + i) = *(source + i);
		i++;
	}

	/* Add the NULL terminator */
	*(p + i) = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	size_t dest_len = strlen(destination);
	char *p = destination + dest_len;

	size_t i = 0;
	/* The same as strcat, but copy the bytes until it reaches the required
	number of bytes, or until it reaches the end of the string */
	while (i < len && *(source + i) != '\0') {
		*(p + i) = *(source + i);
		i++;
	}

	*(p + i) = '\0';

	return destination;
}

int strcmp(const char *str1, const char *str2)
{
	size_t str1_len = strlen(str1);
	size_t str2_len = strlen(str2);

	/* Go through the characters until one interator reaches the end of it's
	string */
	size_t i = 0, j = 0;
	while (i < str1_len && j < str2_len) {
		if (*(str1 + i) > *(str2 + j))
			return 1;

		if (*(str1 + i) < *(str2 + j))
			return -1;

		i++;
		j++;
	}

	/* Check if one string is shorter than the other */
	if (i == str1_len && j < str2_len)
		return -1;

	if (i < str1_len && j == str2_len)
		return 1;

	return 0;
}

int strncmp(const char *str1, const char *str2, size_t len)
{
	size_t str1_len = strlen(str1);
	size_t str2_len = strlen(str2);

	/* Go through the characters until either the iterator reaches the end of
	one string or the maximum number of bytes is reached */
	size_t i = 0;
	while (i < str1_len && i < str2_len && i < len) {
		if (*(str1 + i) > *(str2 + i))
			return 1;

		if (*(str1 + i) < *(str2 + i))
			return -1;

		i++;
	}

	/* If it reached the maximum number -len- of bytes, and it didn't return
	anything, then should return 0, because the required bytes of the strings
	compared are equal */
	if (i == len)
		return 0;

	if (i == str1_len && i < str2_len)
		return -1;

	if (i < str1_len && i == str2_len)
		return 1;

	return 0;
}

size_t strlen(const char *str)
{
	size_t i = 0;

	for (; *str != '\0'; str++, i++)
		;

	return i;
}

char *strchr(const char *str, int c)
{
	char *p = (char *)str;
	while (*p != '\0') {
		/* Return the first address found */
		if (*p == c)
			return p;

		p++;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	char *result = NULL;
	char *p = (char *)str;

	while (*p != '\0') {
		/* If it finds a matching character, store the last address found */
		if (*p == c)
			result = p;

		p++;
	}

	return result;
}

char *strstr(const char *haystack, const char *needle)
{
	char *p = NULL;

	size_t i = 0;
	while (*(haystack + i)) {
		/* If the character doesn't match with the first character of the
		needle, then go to the next character */
		if (*(haystack + i) != *needle) {
			i++;
			continue;
		}

		/* If the characters match, set the pointer p, and check for the other
		characters */
		p = (char *)haystack + i;
		size_t j = 1;
		while (*(haystack + i + j) == *(needle + j) && *(needle + j))
			j++;

		/* If it exists the while loop and needle[i] isn't '\0', then the
		sequence doesn't match, and it should reset p; otherwise, it should
		return p */
		if (*(needle + j))
			p = NULL;
		else
			return p;

		i++;
	}

	return NULL;
}

char *strrstr(const char *haystack, const char *needle)
{
	char *result = NULL;
	char *p = NULL;

	/* Similar approach to strsr, but we'll store the last address found,
	if more than one is matching */
	size_t i = 0;
	while (*(haystack + i)) {
		if (*(haystack + i) != *needle) {
			i++;
			continue;
		}

		p = (char *)haystack + i;
		size_t j = 1;
		while (*(haystack + i + j) == *(needle + j) && *(needle + j))
			j++;

		if (*(needle + j))
			p = NULL;
		else
			result = p;

		i++;
	}

	return result;
}

void *memcpy(void *destination, const void *source, size_t num)
{
	/* Because a char is stored on one byte, cast the pointers to char
	to go through byte by byte */
	char *dest_ptr = (char *)destination;
	char *src_ptr = (char *)source;

	for (size_t i = 0; i < num; i++)
		*(dest_ptr + i) = *(src_ptr + i);

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* Because I don't have acces to malloc function to make a variable 
	size buffer, I will use a static buffer multiple times, if necessary */
	char buffer[BUFF_SIZE];

	char *dest_ptr = (char *)destination;
	char *src_ptr = (char *)source;

	while (num > 0) {
		/* Select how many bytes to move at current iteration */
		size_t bytes;
		if (num < BUFF_SIZE)
			bytes = num;
		else
			num = BUFF_SIZE;

		/* Move the bytes in the buffer */
		for (size_t i = 0; i < bytes; i++)
			buffer[i] = *(src_ptr + i);

		/* Move the bytes from the buffer to the destination */
		for (size_t i = 0; i < bytes; i++)
			*(dest_ptr + i) = buffer[i];

		num = num - bytes;
	}

	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* As it says in the manual, the bytes should be interpreted as
	unsigned char */
	unsigned char *area1 = (unsigned char *)ptr1;
	unsigned char *area2 = (unsigned char *)ptr2;

	for (size_t i = 0; i < num; i++) {
		if (*(area1 + i) > *(area2 + i))
			return 1;

		if (*(area1 + i) < *(area2 + i))
			return -1;
	}

	return 0;
}

void *memset(void *source, int value, size_t num)
{
	char *src = (char *)source;
	char byte = value;

	for (size_t i = 0; i < num; i++)
		*(src + i) = byte;

	return source;
}
