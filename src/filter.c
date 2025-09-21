// filter.c
#include "filter.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

///////////////////////////////
// NoFilter Implementation
///////////////////////////////
float applyNoFilter(Filter* self, float value)
{
    (void)self; // unused
    return value;
}

FilterVtable noFilterVTable = {
    .apply = applyNoFilter
};

typedef struct NoFilterStruct {
    Filter base;
}NoFilterStruct;


///////////////////////////////
// MedianFilter Implementation
///////////////////////////////
#define MEDIAN_SIZE 5

typedef struct MedianFilterStruct {
    Filter base;
    float buffer[MEDIAN_SIZE];
    int count;  // number of valid values
    int index;  // next insert index
} MedianFilterStruct;

// Median helper function
static float median(float* arr, int size)
{
    float temp[MEDIAN_SIZE];
    memcpy(temp, arr, size * sizeof(float));
    // Simple bubble sort
    for(int i=0; i<size-1; i++){
        for(int j=i+1; j<size; j++){
            if(temp[i] > temp[j]){
                float t = temp[i]; temp[i] = temp[j]; temp[j] = t;
            }
        }
    }
    if(size % 2 == 1)
        return temp[size/2];
    else
        return (temp[size/2 -1] + temp[size/2]) / 2.0f;
}

float applyMedianFilter(Filter* self, float value)
{
    MedianFilterStruct* mf = (MedianFilterStruct*)self;
    mf->buffer[mf->index] = value;
    mf->index = (mf->index + 1) % MEDIAN_SIZE;
    if(mf->count < MEDIAN_SIZE) mf->count++;
    return median(mf->buffer, mf->count);
}

FilterVtable medianFilterVTable = {
    .apply = applyMedianFilter
};

// Factory function
Filter* createMedianFilter()
{
    MedianFilterStruct* mf = malloc(sizeof(MedianFilterStruct));
    if(!mf) return NULL;
    mf->base.vtable = &medianFilterVTable;
    mf->count = 0;
    mf->index = 0;
    mf->base.name = "MedianFilter";
    memset(mf->buffer, 0, sizeof(mf->buffer));
    return (Filter*)mf;
}

Filter* createNoFilter() 
{
    NoFilterStruct* mf = malloc(sizeof(NoFilterStruct));
    if(!mf) return NULL;
    mf->base.vtable = &noFilterVTable;
    mf->base.name = "NoFilter";
    return (Filter*)mf;
}

Filter* createFilter(FilterType type)
{
    switch(type)
    {
        case typeNoFilter:
            return createNoFilter();
        case typeMedianFilter:
            return createMedianFilter();
        default:
            return NULL;
    }
}