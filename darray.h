/*
 * darray.h
 *
 * Header file for the darray library, which can make arbitrary
 * multi-dimensional c arrays.
 *
 * Ramses van Zon, 2013
 */

#ifndef _DARRAYH_
#define _DARRAYH_

#include <stddef.h>  /* for size_t */

/** First interface: **/

/* Implemented as a structure */

typedef struct {
  void*   array;           /* Pointer-to-pointer structure       */
  void*   data;            /* Pointer to the contiguous elements */
  size_t  element_size;    /* How big is each element?           */
  size_t  number_extents;  /* How many dimensions are there?     */
  size_t* extent;          /* What are those dimensions?         */
} darray;

/* Mimic the regular malloc/free/calloc/realloc set, but with darray
  instead of void*: (Note: ... is a list of integer extents) */
darray dmalloc(size_t size, size_t nextents, ...);
darray dcalloc(size_t size, size_t nextents, ...);
darray drealloc(darray darr, size_t size, size_t nextents, ...);
void   dfree(darray darr);

/* Function to get the extent in any given dimension. */
size_t dextentof(darray darr, size_t dim);

/*  Accessor/modifier functions (here ... is a list of integer
   indices).  Included for completion, converting to a TYPE** will be
   much faster. */
void dget(void* x, darray a, ...);
void dset(void* x, darray a, ...);

#define DNULL ((darray){ NULL, NULL, 0, 0, NULL })

/** Second interface: **/
void* amalloc(size_t size, size_t nextents, ...);
void* acalloc(size_t size, size_t nextents, ...);
void* arealloc(void* arr, size_t size, size_t nextents, ...);
void  afree(void* arr);

/* Function to get the extent in any given dimension. */
size_t extentof(void* arr, size_t dim);

/* Function to check if this is a darray. */
int isdarray(void* arr);

/** Convert from first to second interface **/

/* Convert to ** or similar */
void* dtoa(darray darr);

/* Convert back from ** to a darray */
darray atod(void* arr);


#endif
