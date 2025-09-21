#ifndef FILTER
#define FILTER

#include <stdlib.h>

typedef struct Filter Filter;

typedef struct 
{
    float (*apply)(Filter* self, float value);
}FilterVtable;

struct Filter
{

    const FilterVtable* vtable;

}FilterVTable;

#endif 