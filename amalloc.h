/*
 * amalloc.h
 *
 * Header file for dynamically allocated multi-dimensional c arrays of
 * arbitrary rank.
 *
 * Copyright (c) 2013 Ramses van Zon
 */

#ifndef _AMALLOC_RVZ_
#define _AMALLOC_RVZ_

#include <stddef.h>   /* for the definition of size_t */

/* 
 * Mimic the regular malloc/free/calloc/realloc set.
 */
void* amalloc(size_t size, size_t rank, ...);
void* acalloc(size_t size, size_t rank, ...);
void* arealloc(void* arr, size_t size, size_t rank, ...);
void  afree(void* arr);
/*
 * Description:
 *
 *  The 'amalloc' function creates a dynamically allocated multi-
 *  dimensional array of dimensions n[0] x n[1] ... x n['rank'-1],
 *  with elements of 'size' bytes.  The dimensions are to be given as
 *  the variable-length arguments.  The function allocates
 *  'size'*n[0]*n[1]*..n['rank'-1] bytes for the data, plus another
 *  n[0]*n[1]*...n[rank-2]*sizeof(void*) bytes for the
 *  pointer-to-pointer structure that is common for c-style arrays.
 *  It also allocates some internal buffers.  The pointer-to-pointer
 *  structure assumes that all pointers are the same size.  The return
 *  value can be cast to a pointer of TYPE* for an array of rank 1,
 *  TYPE** for rank 2, T*** for rank 3, etc., where sizeof(TYPE) must
 *  equal the 'size' argument.  This casted pointer can then be used
 *  in the same way a c-style array is used, i.e., with repeated
 *  square bracket indexing.  If the memory allocation fails, a NULL
 *  pointer is returned.  The return value (or its casted version) can
 *  be used in calls to 'arealloc', 'afree', 'asizeof', 'adata',
 *  'arank', 'ashape', 'aknow', and 'atoda'.  This works because an
 *  internal header containing the information about the
 *  multi-dimensional structure is associated with each dynamicaly
 *  allocated multi-dimensional array.
 *
 *  The 'afree' function frees up all the memory allocated for the
 *  multi-dimensional array associates with the pointer 'arr'.
 *
 *  The 'acalloc' function has the same functionality as 'amalloc',
 *  but also initializes the array to all zeros (by calling 'calloc').
 * 
 *  The 'arealloc' function chances the dimensions and/or the size of
 *  the multi-dimenstional array 'arr'.  The content of the array
 *  will be unchanged in the range from the start of the region up to
 *  the minimum of the old and new sizes.  If the change in dimensions
 *  has changed the shape, the elements get reassigned indices
 *  according to the row-major ordering.  If the re-allocation is
 *  succesful, the new pointer is returned and the old one is invalid.
 *  If the function fails, NULL is returned.  Known bug: the original
 *  'arr' is still deallocated when 'arealloc' fails.
 */

/*
 * Function to get the extent in any given dimension. 
 * This works because an internal header containing the information
 * about the multi-dimensional structure is associated with each
 * dynamicaly allocated multi-dimensional array.
 */
size_t asizeof(void* arr, size_t dim);

/*
 * Function to get the start of the data (useful for library calls).
 * This works because an internal header containing the information
 * about the multi-dimensional structure is associated with each
 * dynamicaly allocated multi-dimensional array.  Returns NULL if no
 * darray is associated with arr.
 */
void* adata(void* arr);

/*
 * Function to get the rank of the multi-dimensional array.  This
 * works because an internal header containing the information about
 * the multi-dimensional structure is associated with each dynamicaly
 * allocated multi-dimensional array.  Returns 0 if no darray is
 * associated with arr.
 */
size_t arank(void* arr);

/*
 * Function to get the shape of the multi-dimensional array This works
 * because an internal header containing the information about the
 * multi-dimensional structure is associated with each dynamicaly
 * allocated multi-dimensional array. Returns NULL if no darray is
 * associated with arr.
 */
const size_t* ashape(void* arr);

/* 
 * Function to check if this is a darray. 
 * This works because an internal header containing the information
 * about the multi-dimensional structure is associated with each
 * dynamicaly allocated multi-dimensional array.
 */
int aknown(void* arr);

#endif

/* end of file amalloc.h */
