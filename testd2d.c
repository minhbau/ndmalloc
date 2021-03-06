#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "ndmalloc.h"

void fill(double** array)
{
    const int n = ndsize(array,0);
    const int m = ndsize(array,1);
    int i, j;
    assert(ndisknown(array));
    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            array[i][j] = i + j;
}

int main()
{
    double ****************************************************************************************************************************************************************************************************************************************************************************** wow_this_can_be_done = 0;
    double** a = ndmalloc(sizeof(double), 2, 10, 4);
    double z = a[9][3]; 
    double** b = calloc(10,sizeof(double*));
    int k;
    fill(a);
    ndfree((void*)a);
    for(k=0;k<10;k++)
        b[k]=calloc(4,sizeof(double));
    /* fill(b);  <-- This would bomb as b is not ndmalloc allocated */
    double **bptr = autoview2(b);
    fill(bptr);
    return wow_this_can_be_done?0:z;
}
