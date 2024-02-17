#include "f2c.h"
#include "fblaswr.h"
#include "clapack.h"


// Rjesavaci sustava
void sor(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal epsilon, doublereal omega);

void cg(integer n, doublereal *A, doublereal *b, doublereal *x, doublereal epsilon);
//

// Metode
void ekspl(integer n, integer m, doublereal delta_x, doublereal delta_t, doublereal *u_a, doublereal *u_b, doublereal *u_0);

void impl(integer n, integer m, doublereal delta_x, doublereal delta_t, doublereal *u_a, doublereal *u_b, doublereal *u_0, char rjesavac);

void cn(integer n, integer m, doublereal delta_x, doublereal delta_t, doublereal *u_a, doublereal *u_b, doublereal *u_0, char rjesavac);
//