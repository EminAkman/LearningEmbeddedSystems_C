#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Sensor base;
    float currentTemp;
} TempSensor;

static SensorError temp_init(Sensor* self) {
    TempSensor* ts = (TempSensor*)self;
    ts->currentTemp = 25.0f;
    return SENSOR_OK;
}

static SensorError temp_read(Sensor* self, float* value) {
    TempSensor* ts = (TempSensor*)self;
    ts->currentTemp += ((rand() % 100)/100.0f) - 0.5f;
    *value = ts->currentTemp;

    if(ts->base.filter)
    {
        *value = ts->base.filter->vtable->apply(ts->base.filter, *value);

        printf("Sensor bir %s sensorudur. %s filtresinden gecirilmistir ve mesafe: %f m'dir. ID'si : %d'dir.\n",
        ts->base.name,ts->base.filter->name,ts->currentTemp, ts->base.ID);
    }

    return SENSOR_OK;
}

static SensorError temp_calibrate(Sensor* self) {
    return SENSOR_OK;
}

static void temp_destroy(Sensor* self) {
    if(self->filter) free(self->filter);
    free(self);
}

static void temp_check_callback(Sensor* self) {
    TempSensor* ts = (TempSensor*)self;
    
    for (int i = 0; i < sizeof(CallbackType) / 4; i++)
    {
        if (ts->base.callback == typeVerify && ts->currentTemp == *ts->base.tresholdcallback)
        {
            printf("Uyari sensor %f esik degerini asti!!!", ts->base.tresholdcallback);
        }        
    }
}

static const SensorVTable temp_vtable = {
    .init = temp_init,
    .read = temp_read,
    .calibrate = temp_calibrate,
    .destroy = temp_destroy,
    .checkCallback = temp_check_callback,
};

Sensor* TempSensor_create() {
    TempSensor* ts = malloc(sizeof(TempSensor));
    if(!ts) return NULL;
    ts->base.vtable = &temp_vtable;
    ts->base.name = "TempSensor";
    ts->currentTemp = 0;
    ts->base.filter = createFilter(typeNoFilter);
    ts->base.callback = typeNoCallback;
    SensorID++;
    ts->base.ID = SensorID;
    return (Sensor*)ts;
}
