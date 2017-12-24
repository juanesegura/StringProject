#include <stdlib.h>
#include "String.h"

/* 
 * Juan Segura juan97
 * 
 * String.c
 *
 */


/** The String is initialized to hold the values in *src.
 *
 *  Pre:
 *    *src is C string with length up to slength (excludes null char)
 *  Post on success:
 *    A new, proper String object S is created such that:
 *       S.data != src
 *       Up to slength characters in *src are copied into dest->data
 *         (after dynamic allocation) and the new string is terminated
 *         with a '\0'
 *       Slength is set to the number of characters copied from *src;
 *         this is no more than slength, but will be less if a '\0' is
 *         encountered in *src before slength chars have occurred
 * Post on failure:
 *    NULL is returned
 * s
 * Returns:
 *    pointer to the new String object;
 *    NULL value if some error occurs
 */
String* String_Create(const char* const src, uint32_t slength) {

	if(slength < 0 || src == NULL) { return NULL; }
	
	String *s = malloc(sizeof(String));
	s->length = 0;
	s->data = malloc((slength+1) * sizeof(char));
	
	for(int i = 0; i < slength; i++) {
		if(*(src+i) == '\0') {
			break;
		}
		*(s->data + i) = *(src+i);
		s->length ++;
	}
	
	*(s->data + s->length) = '\0';
	s->data = realloc(s->data, s->length+1);
	return s;
}


/** Appends the String *src to the String *dest.
 * 
 *  Pre:
 *    *dest is a proper String object
 *    *src is is a proper String object
 *    src != dest
 *  Post on success:
 *    *src is appended to the String *dest
 *    *dest is a proper String object  
 *  Post on failure:
 *    dest->data == NULL, dest->length == 0
 * 
 *  Returns:
 *    the length of dest->data, if nothing goes wrong;
 *    a negative value, if some error occurs
 */
int32_t String_Cat(String* const dest, const String* const src) {
	if(src == NULL) { 
		dest->data = NULL;
		dest ->length = 0;
		return -1; 
	}

	int32_t desCount = 0;
	int32_t srcCount = 0;
	dest->data = realloc(dest->data, dest->length + src->length + 1);
	dest->length = dest->length + src->length;
	
	while(*(dest->data + desCount) != '\0') {
			desCount++;
	}
	
	while(*(src->data + srcCount) != '\0') {
		*(dest->data + desCount) = *(src->data+srcCount);
		srcCount++;
		desCount++;
	}
	*(dest->data + dest->length) = '\0';
	
	return dest->length;
}


/** Makes an exact, full copy of a substring.
 * 
 * Pre:
 *   *src is a proper String object
 *   startIdx + length <= src->length
 * Post:
 *    no memory leaks have occurred
 *	   A new, proper string object S has been created such that S holds
 *      the specified substring of *src
 *
 * Returns:
 *	  pointer to a String object which holds a copy of specified substring;
 *   NULL if failure occurs
 */
String* String_subString(const String* const src, uint32_t start, uint32_t length) {
	if(src == NULL || (start+length) > src->length || start < 0 || length < 0) 
		{ return NULL; }
		
	String *s = malloc(sizeof(String));
	s->length = length;
	s->data = malloc((length+1) * sizeof(char));
	
	for(int i = 0; i < length; i++) {
		*(s->data + i) = *(src->data + start);
		start++;
	}
	
	
	*(s->data + s->length) = '\0';
	s->data = realloc(s->data, s->length+1);
	return s;
}


/** Erases a specified sequence of characters from a String.
 * 
 * Pre:
 *   *src is a proper String object
 *   startIdx + length <= src->length
 * Post:
 *    no memory leaks have occurred
 *    the specified range of characters have been removed
 *	   *src is proper
 *
 * Returns:
 *	  if successful, src
 *   NULL if failure occurs
 */
String* String_Erase(String* const src, uint32_t start, uint32_t length) {
	if(src == NULL || (start+length) > src->length || start < 0 || length < 0) 
		{ return NULL; }
	
	for(int i = start; i < src->length - length; i++) {
		*(src->data + i) = *(src->data + i + length);
	}

	src->length = src->length - length;
	
	*(src->data + src->length) = '\0';
	src->data = realloc(src->data, src->length+1);
	return src;
}


/** Makes an exact, full copy of a String.
 * 
 * Pre:
 *   *src is a proper String object
 * Post:
 *    no memory leaks have occurred
 *	   A new, proper string object S has been created such that S is a
 *      copy of S
 *
 * Returns:
 *	  pointer to a String object which holds a copy of *src;
 *   NULL if failure occurs
 */
String* String_Copy(const String* const  src) {
	if(src == NULL) { return NULL; }
	
	String *s = malloc(sizeof(String));
	
	s->length = src->length;
	s->data = malloc((src->length+1) * sizeof(char));
	
	for(int i = 0; i < src->length; i++) {
		*(s->data + i) = *(src->data +i);
	}
	
	*(s->data + s->length) = '\0';
	s->data = realloc(s->data, s->length+1);
	return s;
}


/** Compares two Strings.
 * 
 *  Pre:
 *    *left is a proper String object
 *    *right is is a proper String object
 *
 *  Returns:
 *    < 0 if left precedes right, lexically
 *      0 if left equals right
 *    > 0 if left follows right, lexically
 */
int32_t String_Compare(const String* const left, const String* const right) {
	int32_t count = 0;
	while(*(left->data + count) == *(right->data + count)) {
		if(*(left->data + count) == '\0' || *(right->data + count) == '\0') {
			break;
		}
		count++;
	}
	if(*(left->data + count) == '\0' && count == 0 && *(right->data + count) == '\0') {
			return 0;
	} else if(*(left->data + count) == '\0' && count == 0 && *(right->data + count) != '\0') {
			return -1;
	} else if(*(left->data + count) != '\0' && count == 0 && *(right->data + count) == '\0') {
			return 1;
	}
	
	

	if(*(left->data + count) == '\0' && *(right->data + count) == '\0') {
		return *(left->data + count - 1) - *(right->data + count-1);
	} 
	else if (*(left->data + count) == '\0') {
		if(*(left->data + count - 1) == *(right->data + count-1)) {
			return -1;
		} else {
			return *(left->data + count-1) - *(right->data + count-1);
		}
	} 
	else if (*(right->data + count) == '\0') {
		if(*(left->data + count - 1) == *(right->data + count-1)) {
				return 1;
		} else {
			return *(left->data + count-1) - *(right->data + count-1);
		}
	} 
	else {
		return *(left->data + count) - *(right->data + count);
	} 
}

/**  Deallocates a String object and all its content.
 * 
 *   Pre:
 *     **str is a proper String object
 *     **str was allocated dynamically
 *   Post:
 *     (**str).data has been deallocated
 *     **str has been deallocated
 *     *str == NULL
 */
void String_Dispose(String** str) {
	free((*str)->data);
	free(*str);
	*str = NULL;
}
