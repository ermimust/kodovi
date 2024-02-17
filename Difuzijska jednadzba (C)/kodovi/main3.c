#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "difuz_jed.h"


int main()
{
    // Mreza
    integer n = 140,
            m = 90;
    //

    // Rubovi
    doublereal a = 17.3511, b = 88.1254151,
               T = 12.87;

    doublereal delta_x = (b - a) / (doublereal)n,
               delta_t = T / (doublereal)m;
    //

    // Pocetni uvjeti
    integer i;

    doublereal *u_a;
    u_a = (doublereal *)malloc(m * sizeof(doublereal));

    for (i = 0; i < m; i++)
    {
        u_a[i] = 100.0;
    }

    doublereal *u_b;
    u_b = (doublereal *)malloc(m * sizeof(doublereal));

    for (i = 0; i < m; i++)
    {
        u_b[i] = 110.0;
    }

    doublereal *u_0;
    u_0 = (doublereal *)malloc((n+1) * sizeof(doublereal));

    u_0[0] = 100.0;

    for (i = 1; i <= n-1; i++)
    {
        u_0[i] = i * log((doublereal)(i+1));
    }

    u_0[n] = 110.0;
    //

    // Potpuna implicitna metoda konacnih razlika
    impl(n, m, delta_x, delta_t, u_a, u_b, u_0, 'g');

    printf("\n");
    impl(n, m, delta_x, delta_t, u_a, u_b, u_0, 'c');
    //

    // Crank-Nicolsonova metoda
    printf("\n");
    cn(n, m, delta_x, delta_t, u_a, u_b, u_0, 'g');

    printf("\n");
    cn(n, m, delta_x, delta_t, u_a, u_b, u_0, 'c');
    //

    free(u_a);
    free(u_b);
    free(u_0);

    return 0;
}