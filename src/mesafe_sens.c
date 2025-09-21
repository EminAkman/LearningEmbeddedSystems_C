#include "sensor.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Sensor base;        // Inheritance by composition
    float currentDistance;
} MesafeSensor;

static SensorError mesafeSens_Init(Sensor* self) {
    MesafeSensor* ms = (MesafeSensor*) self;
    ms->currentDistance = 2;  
    return SENSOR_OK;
}

static SensorError mesafeSens_Read(Sensor* self, float* distance){
    MesafeSensor* ms = (MesafeSensor*) self;
    ms->currentDistance += ((rand() % 100) / 100.0f) - 0.5f;
    *distance = ms->currentDistance; 
    float filteredDistance = ms->base.filter.vtable->apply(&ms->base.filter,*distance);
    printf("Sensor bir %s sensorudur. Ve mesafesi: %f m'dir. ID'si : %d'dir.\n",ms->base.name,ms->currentDistance, ms->base.ID);
    return SENSOR_OK;
}

static SensorError mesafeSens_Calibrate(Sensor* self){
    return SENSOR_OK;
}

static void mesafeSens_Destroy(Sensor* self){
    free(self);
}

static SensorVTable mesafeSens_Vtable = {
    .init = mesafeSens_Init,
    .read = mesafeSens_Read,
    .calibrate = mesafeSens_Calibrate,
    .destroy = mesafeSens_Destroy,
};

Sensor* CreateMesafeSens() {
    MesafeSensor* Ms = malloc(sizeof(MesafeSensor));
    if (!Ms) return NULL;
    Ms->currentDistance = 0;
    Ms->base.name = "MesafeSens";
    Ms->base.vtable = &mesafeSens_Vtable;
    SensorID++;
    Ms->base.ID = SensorID;
    return (Sensor*)Ms;
}