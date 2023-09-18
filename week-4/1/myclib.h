#ifndef MYCLIB_H_
#define MYCLIB_H_

typedef struct Dinges {
  const char *name;
  int value;
} Dinges;

Dinges *create_dinges();
void destroy_dinges(Dinges *dinges);

#endif // MYCLIB_H_