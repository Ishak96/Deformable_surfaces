#include <minimization.h>

double fn1 (double x, void * params) {
	(void)(params); /* avoid unused parameter warning */
	return cos(x) + 1.0;
}