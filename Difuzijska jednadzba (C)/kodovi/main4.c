#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "difuz_jed.h"


int main()
{
    // Mreza
    integer n = 10,
            m = 50;
    //

    // Rubovi
    doublereal a = 0, b = 1,
               T = 0.5;

    doublereal delta_x = (b - a) / (doublereal)n,
               delta_t = T / (doublereal)m;
    //

    // Pocetni uvjeti
    integer i;

    doublereal *u_a;
    u_a = (doublereal *)calloc(m, sizeof(doublereal));

    doublereal *u_b;
    u_b = (doublereal *)calloc(m, sizeof(doublereal));

    doublereal *u_0;
    u_0 = (doublereal *)malloc((n+1) * sizeof(doublereal));

    for (i = 0; i < n+1; i++)
    {
        u_0[i] = sin(M_PI * i / (doublereal)n);
    }
    //

    ekspl(n, m, delta_x, delta_t, u_a, u_b, u_0);

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

    // Egzaktno rjesenje
    printf("\n[Egzaktno rjesenje] e^-(pi*pi*T) * sin(pix)\n");

    for (i = 0; i < n+1; i++)
    {
        printf("    %lg\n", pow(M_E, -(M_PI * M_PI) * T) * sin(M_PI * i / (doublereal)n));
    }
    //

    free(u_a);
    free(u_b);
    free(u_0);

    return 0;
}