#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "difuz_jed.h"


void cg(integer n, doublereal *A, doublereal *b, doublereal *x0, doublereal tol)
{
    // r
    char upper = 'U';

    integer inc = 1;

    doublereal alpha = -1.0, beta = 1.0, *r;
    r = (doublereal *)malloc(n * sizeof(doublereal));

    dcopy_(&n, b, &inc, r, &inc);  // r = b

    dsymv_(&upper, &n, &alpha, A, &n, x0, &inc, &beta, r, &inc);  // r = A*x0 - b
    //

    // d
    doublereal *d;
    d = (doublereal *)malloc(n * sizeof(doublereal));

    dcopy_(&n, r, &inc, d, &inc);  // d = r
    //

    // ||b||_2
    doublereal norm2_b;
    norm2_b = dnrm2_(&n, b, &inc);  // norm2_b = ||b||_2
    //

    // x
    doublereal skProd_dAd, skProd_r, skProd_r2, norm2_r;
    skProd_r = ddot_(&n, r, &inc, r, &inc);  // skPord_r = r^T * r
    norm2_r = sqrt(skProd_r);

    doublereal alpha2 = 1.0, beta2 = 0.0, alpha_k, beta_k, *temp, *res;
    temp = (doublereal *)calloc(n, sizeof(doublereal));
    res = (doublereal *)calloc(2*n, sizeof(doublereal));

    res[0] = norm2_r / norm2_b;

    integer k = 0;
    while (!(norm2_r / norm2_b < tol))
    {
        ++k;

        dsymv_(&upper, &n, &alpha2, A, &n, d, &inc, &beta2, temp, &inc);  // temp = Ad

        skProd_dAd = ddot_(&n, d, &inc, temp, &inc);  // skProd_dAd = (d|Ad)

        alpha_k = skProd_r / skProd_dAd;

        daxpy_(&n, &alpha_k, d, &inc, x0, &inc);  // x = x + alpha_k * d

        alpha_k = -alpha_k;
        daxpy_(&n, &alpha_k, temp, &inc, r, &inc);  // r = r - alpha_k * Ad

        skProd_r2 = ddot_(&n, r, &inc, r, &inc);  // skProd_r2 = (r|r)

        beta_k = skProd_r2 / skProd_r;

        dcopy_(&n, d, &inc, temp, &inc);  // temp = d

        dcopy_(&n, r, &inc, d, &inc);  // d = r

        daxpy_(&n, &beta_k, temp, &inc, d, &inc);  // d = r + beta_k * d

        norm2_r = sqrt(skProd_r2);
        skProd_r = skProd_r2;
        res[k] = norm2_r / norm2_b;
    }
    //

    free(r);
    free(d);
    free(temp);
    
    return;
}