#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <filter.h>
#include <enums.h>

typedef struct Sensor Sensor;

typedef struct
{

    SensorError (*init)(Sensor *self);
    SensorError (*read)(Sensor *self, float *value);
    SensorError (*calibrate)(Sensor *self);
    void (*destroy)(Sensor *self);
    void (*checkCallback)(Sensor *self);

} SensorVTable;

struct Sensor
{
    const SensorVTable *vtable;
    const char *name;
    int ID;
    Filter *filter;
    CallbackType callback;
    float tresholdcallback;
};

extern int SensorID;

#endif
