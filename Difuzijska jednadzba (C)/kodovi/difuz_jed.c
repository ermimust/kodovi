#include <stdio.h>
#include <stdlib.h>

#include "difuz_jed.h"


void ekspl(integer n, integer m, doublereal delta_x, doublereal delta_t, doublereal *u_a, doublereal *u_b, doublereal *u_0)
{
    integer i, j;
    
    doublereal lambda = delta_t / (delta_x * delta_x);

    // u_stari
    integer nn = n+1, inc = 1;

    doublereal *u_stari;
    u_stari = (doublereal *)malloc((n+1) * sizeof(doublereal));

    dcopy_(&nn, u_0, &inc, u_stari, &inc);  // u_stari = u_0
    //

    // u
    doublereal *u;
    u = (doublereal *)malloc((n+1) * sizeof(doublereal));

    for (j = 0; j < m; j++)
    {
        u[0] = u_a[j];
        u[n] = u_b[j];

        for (i = 1; i <= n-1; i++)
        {
            u[i] = lambda * u_stari[i-1] + (1 - 2*lambda) * u_stari[i] + lambda * u_stari[i+1];
        }

        dcopy_(&nn, u, &inc, u_stari, &inc);  // u_stari = u
    }
    //

    // Ipsis
    printf("[Eksplicitna metoda konacnih razlika] u(a + i*delta_x, T) =\n");

    for (i = 0; i <= n; i++)
    {
        printf("    %lg\n", u[i]);
    }
    //

    free(u_stari);
    free(u);

    return;
}

void impl(integer n, integer m, doublereal delta_x, doublereal delta_t, doublereal *u_a, doublereal *u_b, doublereal *u_0, char rjesavac)
{
    integer i, j;

    integer nn = n+1, nnn = n-1;
    
    doublereal lambda = delta_t / (delta_x * delta_x);

    // A
    doublereal *A;
    A = (doublereal *)malloc((n-1)*(n-1) * sizeof(doublereal));
    
    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-1; j++)
        {
            if(i == j)
            {
                A[i + j*(n-1)] = 1.0 + 2.0 * lambda;
            }

            else if(i == j+1 || i+1 == j)
            {
                A[i + j*(n-1)] = -lambda;
            }

            else
            {
                A[i + j*(n-1)] = 0.0;
            }
        }
    }
    //

    // u
    integer inc = 1;

    doublereal *u, *b;
    u = (doublereal *)malloc((n+1) * sizeof(doublereal));
    b = (doublereal *)malloc((n-1) * sizeof(doublereal));

    dcopy_(&nn, u_0, &inc, u, &inc);  // u = u_0

    for (j = 0; j < m; j++)
    {
        dcopy_(&nnn, u+1, &inc, b, &inc);  // b = u(1:n-1)

        u[0] = u_a[j];
        u[n] = u_b[j];

        b[0] += lambda * u[0];
        b[n-2] += lambda * u[n];

        if (rjesavac == 'g')
        {
            sor(nnn, A, b, u+1, 1e-8, 1.0);
        }

        if (rjesavac == 'c')
        {
            cg(nnn, A, b, u+1, 1e-8);
        }
    }
    //

    // Ispis
    printf("[Potpuna implicitna metoda konacnih razlika | ");
    
    if (rjesavac == 'g')
    {
        printf("Gauss-Seidel] u(a + i*delta_x, T) =\n");
    }

    if (rjesavac == 'c')
    {
        printf("Konjugirani gradijenti] u(a + i*delta_x, T) =\n");
    }

    for (i = 0; i <= n; i++)
    {
        printf("    %lg\n", u[i]);
    }
    //
    
    free(A);
    free(u);
    free(b);

    return;
}

void cn(integer n, integer m, doublereal delta_x, doublereal delta_t, doublereal *u_a, doublereal *u_b, doublereal *u_0, integer1 rjesavac)
{
    integer i, j;

    integer nn = n+1, nnn = n-1, inc = 1;
    
    doublereal lambda = delta_t / (delta_x * delta_x);

    // A
    doublereal *A;
    A = (doublereal *)malloc((n-1)*(n-1) * sizeof(doublereal));

    for(i = 0; i < n-1; i++)
    {
        for(j = 0; j < n-1; j++)
        {
            if(i == j)
            {
                A[i + j*(n-1)] = 1.0 + lambda;
            }

            else if(i == j+1 || i+1 == j)
            {
                A[i + j*(n-1)] = -lambda / 2.0;
            }

            else
            {
                A[i + j*(n-1)] = 0.0;
            }
        }
    }
    //

    // u
    doublereal *u, *b;
    u = (doublereal *)malloc((n+1) * sizeof(doublereal));
    b = (doublereal *)malloc((n-1) * sizeof(doublereal));

    dcopy_(&nn, u_0, &inc, u, &inc);  // u = u_0

    for(j = 0; j < m; j++)
    {
        for(i = 0; i < n-1; i++)
        {
            b[i] = (lambda / 2.0) * u[i] + (1.0 - lambda) * u[i+1] + (lambda / 2.0) * u[i+2];
        }

        u[0] = u_a[j];
        u[n] = u_b[j];

        b[0] += (lambda / 2.0) * u[0];
        b[n-2] += (lambda / 2.0) * u[n];
        
        if(rjesavac == 'g')
        {
            sor(nnn, A, b, u+1, 1e-8, 1.0);
        }
        
        if(rjesavac == 'c')
        {
            cg(nnn, A, b, u+1, 1e-8);
        }
    }
    //

    // Ispis
    printf("[Crank-Nicolsonova metoda | ");

    if (rjesavac == 'g')
    {
        printf("Gauss-Seidel] u(a + i*delta_x, T) =\n");
    }

    if (rjesavac == 'c')
    {
        printf("Konjugirani gradijenti] u(a + i*delta_x, T) =\n");
    }

    for (i = 0; i <= n; i++)
    {
        printf("    %lg\n", u[i]);
    }
    //
    
    free(A);
    free(u);
    free(b);

    return;
}