// SPDX-License-Identifier: BSD-3-Clause

#include <string.h>

char *strcpy(char *destination, const char *source)
{
	size_t i = 0;
	while (*(source + i) != '\0') {
		*(destination + i) = *(source + i);
		i++;
	}

	*(destination + i) = '\0';

	return destination;
}

char *strncpy(char *destination, const char *source, size_t len)
{
	size_t i = 0;
	while (*(source + i) != '\0' && i < len) {
		*(destination + i) = *(source + i);
		i++;
	}

	while (i < len) {
		*(destination + i) = '\0';
		i++;
	}

	return destination;
}

char *strcat(char *destination, const char *source)
{
	size_t dest_len = strlen(destination);
	char *p = destination + dest_len;

	size_t i = 0;
	while (*(source + i) != '\0') {
		*(p + i) = *(source + i);
		i++;
	}

	*(p + i) = '\0';

	return destination;
}

char *strncat(char *destination, const char *source, size_t len)
{
	size_t dest_len = strlen(destination);
	char *p = destination + dest_len;

	size_t i = 0;
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

	// Go through the characters until one interator reaches the end of it's
	// string
	size_t i = 0, j = 0;
	while (i < str1_len && j < str2_len) {
		if (*(str1 + i) > *(str2 + j))
			return 1;

		if (*(str1 + i) < *(str2 + j))
			return -1;

		i++;
		j++;
	}

	// Check if one string is shorter than other
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

	// Go through the characters until either the iterator reaches the end of
	// one string or the maximum number -len- of bytes is reached
	size_t i = 0;
	while (i < str1_len && i < str2_len && i < len) {
		if (*(str1 + i) > *(str2 + i))
			return 1;

		if (*(str1 + i) < *(str2 + i))
			return -1;

		i++;
	}

	// If it reached the maximum number -len- of bytes, and it didn't return
	// anything, then should return 0, because the -len- bytes of the strings
	// compared are equal
	if (i == len)
		return 0;

	// If one string is shorter than the other, and is also shorter than len
	// bytes, check which string has reached the end
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
	char *p = str;
	while (*p != '\0') {
		if (*p == c)
			return p;

		p++;
	}

	return NULL;
}

char *strrchr(const char *str, int c)
{
	char *result = NULL;
	
	char *p = str;
	while (*p != '\0') {
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
		// If the character doesn't match with the first character of the
		// needle, then go to the next character
		if (*(haystack + i) != *needle) {
			i++;
			continue;
		}

		// If the characters match, set the pointer p, and check for the other
		// characters
		p = haystack + i;
		size_t j = 1;
		while (*(haystack + i + j) == *(needle + j) && *(needle + j))
			j++;

		// If it exists the while loop and needle[i] isn't '\0', then the
		// sequence doesn't match, and it should reset p; otherwise, it should
		// return p
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

	// Similiar approach to strstr
	size_t i = 0;
	while (*(haystack + i)) {
		if (*(haystack + i) != *needle) {
			i++;
			continue;
		}

		p = haystack + i;
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
	// Make some pointers using the fact that a char has 1 byte
	char *dest_ptr = (char *)destination;
	char *src_ptr = (char *)source;

	for (size_t i = 0; i < num; i++) {
		*(dest_ptr + i) = *(src_ptr + i);
	}

	return destination;
}

void *memmove(void *destination, const void *source, size_t num)
{
	/* TODO: Implement memmove(). */
	return destination;
}

int memcmp(const void *ptr1, const void *ptr2, size_t num)
{
	/* TODO: Implement memcmp(). */
	return -1;
}

void *memset(void *source, int value, size_t num)
{
	/* TODO: Implement memset(). */
	return source;
}
