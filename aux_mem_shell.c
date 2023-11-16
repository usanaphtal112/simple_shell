#include "shell.h"

/**
 * @brief Reallocates memory for an array of pointers.
 *
 * Resizes the array of pointers pointed to by 'ptr' to 'new_size' elements.
 * The content of the array is preserved up to the minimum
 * If the new size is larger, the additional elements are uninitialized.
 *
 * @param ptr Pointer to the array of pointers to be reallocated.
 * @param old_size Number of elements in the current array.
 * @param new_size Number of elements to resize the array to.
 * @return Pointer to the reallocated array of pointers.
 */
char **_reallocdp(char **ptr, unsigned int old_size, unsigned int new_size)
{
    char **newptr;
    unsigned int i;

    if (ptr == NULL)
        return (malloc(sizeof(char *) * new_size));

    if (new_size == old_size)
        return (ptr);

    newptr = malloc(sizeof(char *) * new_size);
    if (newptr == NULL)
        return (NULL);

    for (i = 0; i < old_size; i++)
        newptr[i] = ptr[i];

    free(ptr);

    return (newptr);
}

/**
 * @brief Reallocates memory for a block of memory.
 *
 * Resizes the memory block pointed to by 'ptr' to 'new_size' bytes. The content
 * of the block is preserved up to the minimum of the old and new sizes. If the
 * new size is larger, the additional memory is not initialized.
 *
 * @param ptr Pointer to the memory block to be reallocated.
 * @param old_size Size of the current memory block.
 * @param new_size Size to resize the memory block to.
 * @return Pointer to the reallocated memory block.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
    void *newptr;

    if (ptr == NULL)
        return (malloc(new_size));

    if (new_size == 0)
    {
        free(ptr);
        return (NULL);
    }

    if (new_size == old_size)
        return (ptr);

    newptr = malloc(new_size);
    if (newptr == NULL)
        return (NULL);

    if (new_size < old_size)
        _memcpy(newptr, ptr, new_size);
    else
        _memcpy(newptr, ptr, old_size);

    free(ptr);
    return (newptr);
}

/**
 * @brief Copies data from one memory location to another.
 *
 * Copies 'size' bytes from the memory area pointed to by 'ptr' to the memory
 * area pointed to by 'newptr'. The memory areas must not overlap.
 *
 * @param newptr Pointer to the destination memory location.
 * @param ptr Pointer to the source memory location.
 * @param size Number of bytes to copy.
 */
void _memcpy(void *newptr, const void *ptr, unsigned int size)
{
    char *char_ptr = (char *)ptr;
    char *char_newptr = (char *)newptr;
    unsigned int i;

    for (i = 0; i < size; i++)
        char_newptr[i] = char_ptr[i];
}
