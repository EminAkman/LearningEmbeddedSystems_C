#ifndef FILTER
#define FILTER

#include <stdlib.h>
#include <enums.h>

typedef struct Filter Filter;
typedef struct FilterVtable FilterVtable;

typedef struct Filter
{
    FilterVtable* vtable;
    const char* name;
}Filter;

typedef struct FilterVtable
{
    float (*apply)(Filter* self, float value);
}FilterVtable;

Filter* createFilter(FilterType type);

#endif 