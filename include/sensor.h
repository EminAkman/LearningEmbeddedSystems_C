#ifndef SENSOR_H
#define SENSOR_H

#include <stdint.h>
#include <filter.h>

// Hata kodları
typedef enum {
    SENSOR_OK = 0,
    SENSOR_ERROR = 1,
} SensorError;

extern int SensorID;

// Öneki: Opaque pointer ile encapsulation
typedef struct Sensor Sensor;

// Vtable: fonksiyon pointer'ları (Interface / Polymorphism)
typedef struct {
    SensorError (*init)(Sensor* self);
    SensorError (*read)(Sensor* self, float* value);
    SensorError (*calibrate)(Sensor* self);
    void (*destroy)(Sensor* self);
} SensorVTable;

// Sensor struct (opaque, detay .c'de olacak)
struct Sensor {
    const SensorVTable* vtable;  // Pointer to function table
    const char* name;
    int ID;
    Filter filter;
};

#endif // SENSOR_H
