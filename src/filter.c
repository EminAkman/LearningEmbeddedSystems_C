#ifndef FILTER_C
#define FILTER_C

#include "filter.h"

typedef struct 
{
    FilterVtable* vtable;
    float buffer[5];
    int index;
    int count;
} medianFilter;

///////////////////////////////
// NoFilter Implementation
///////////////////////////////

float applyNoFilter(Filter* self, float value)
{
    return value;
}

FilterVtable noFilterVTable=
{
    .apply = applyNoFilter,
};

Filter NoFilter =
{
    .vtable = &noFilterVTable,
};


///////////////////////////////
// MedianFilter Implementation
///////////////////////////////

float applyMedianFilter(Filter* self, float value)
{
    medianFilter* mf = (medianFilter*) self;
    mf->buffer[mf->index] = value;
    mf->index = (mf->index + 1) % 5;
    if (mf->count < 5) mf->count++;

    return value;
}

FilterVtable medianFilterVTable=
{
    .apply = applyMedianFilter,
};



// Factory function to create filters

Filter* createFilter(FilterType type){
    
    Filter* f = malloc(sizeof(Filter));
    if(!f) return NULL;

    switch (type)
    {
    case typeNoFilter:
        f->vtable = &noFilterVTable;
        
        return f;
    case typeMedianFilter:
        f->vtable = &medianFilterVTable;
        
        return f;
    }
}

#endif