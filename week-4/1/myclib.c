#include "myclib.h"
#include <stdlib.h> // for malloc and free

Dinges *create_dinges() { return (Dinges *)malloc(sizeof(Dinges)); }

void destroy_dinges(Dinges *dinges) { free(dinges); }