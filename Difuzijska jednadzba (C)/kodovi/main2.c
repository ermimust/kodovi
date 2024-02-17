#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "difuz_jed.h"


int main()
{
    // Mreza
    integer n = 100,
            m = 100;
    //

    // Rubovi
    doublereal a = 0.0, b = 1.0,
               T = 1.0;

    doublereal delta_x = (b - a) / (doublereal)n,
               delta_t = T / (doublereal)m;
    //

    // Pocetni uvjeti
    doublereal *u_a, *u_b;
    u_a = (doublereal *)calloc(m, sizeof(doublereal));
    u_b = (doublereal *)calloc(m, sizeof(doublereal));

    doublereal *u_0;
    u_0 = (doublereal *)malloc((n+1) * sizeof(doublereal));

    integer i;
    for (i = 0; i <= n; i++)
    {
        u_0[i] = 300.0 * sin((M_PI * i) / (doublereal)n);
    }
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