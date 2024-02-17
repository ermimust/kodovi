#include <stdio.h>
#include <stdlib.h>

#include "difuz_jed.h"


void sor(integer n, doublereal *A, doublereal *b, doublereal *x0, doublereal tol, doublereal omega)
{
    // ||b||
    integer inc = 1;

    doublereal norm2_b;
    norm2_b = dnrm2_(&n, b, &inc);  // norm2_b = ||b||_2
    //

    // ||r||_2
    char normal = 'N';

    doublereal alpha = -1.0, beta = 1.0, *r;
    r = (doublereal *)malloc(n * sizeof(doublereal));

    dcopy_(&n, b, &inc, r, &inc);  // r = b

    dgemv_(&normal, &n, &n, &alpha, A, &n, x0, &inc, &beta, r, &inc); // r = A*x0 - b

    doublereal norm2_r;
    norm2_r = dnrm2_(&n, r, &inc);  // norm2_r = ||r||_2
    //
    
    // x
    integer i, j, k = 0;

    doublereal temp;

    while (!(norm2_r / norm2_b <= tol))
    {
        ++k;

        for (i = 0; i < n; i++)
        {
            x0[i] *= 1.0 - omega;

            temp = b[i];

            for (j = 0; j < i; j++)
            {
                temp -= A[i + j*n] * x0[j];
            }

            for (j = i + 1; j < n; j++)
            {
                temp -= A[i + j*n] * x0[j];
            }

            x0[i] += temp * omega / A[i + i*n];
        }

        dcopy_(&n, b, &inc, r, &inc);  // r = b

        dgemv_(&normal, &n, &n, &alpha, A, &n, x0, &inc, &beta, r, &inc);  // r = A*x0 - b

        norm2_r = dnrm2_(&n, r, &inc);  // norm2_r = ||r||_2
    }
    //

    free(r);

    return;
}