#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>

// İç yapı (opaque pointer için)
typedef struct {
    Sensor base;        // Inheritance by composition
    float currentTemp;
} TempSensor;

// Fonksiyonlar
static SensorError temp_init(Sensor* self) {
    TempSensor* ts = (TempSensor*)self; 
    ts->currentTemp = 25.0; // varsayılan sıcaklık
    return SENSOR_OK;
}

static SensorError temp_read(Sensor* self, float* value) {
    TempSensor* ts = (TempSensor*)self;
    // Simülasyon: random değer üret
    ts->currentTemp += ((rand() % 100) / 100.0f) - 0.5f;
    *value = ts->currentTemp;
    printf("Sensor bir %s sensorudur. Ve derece: %f C'dir. ID'si : %d'dir.\n",ts->base.name,ts->currentTemp, ts->base.ID);
    return SENSOR_OK;
}

static SensorError temp_calibrate(Sensor* self) {
    return SENSOR_OK;
}

static void temp_destroy(Sensor* self) {
    free(self);
}

// Vtable instance
static const SensorVTable temp_vtable = {
    .init = temp_init,
    .read = temp_read,
    .calibrate = temp_calibrate,
    .destroy = temp_destroy
};

// Public create function
Sensor* TempSensor_create() {
    TempSensor* ts = malloc(sizeof(TempSensor));
    if (!ts) return NULL;
    ts->base.vtable = &temp_vtable;
    ts->base.name = "TempSensor";
    ts->currentTemp = 0.0f;
    SensorID++;
    ts->base.ID = SensorID;
    return (Sensor*)ts;
}
