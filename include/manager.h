#ifndef MANAGER_H
#define MANAGER_H

#include "sensor.h"
#include <stdint.h>

#define MAX_SENSORS 32

typedef struct 
{   
    Sensor* sensors[MAX_SENSORS];
    const int count;
}SensorManger;

SensorError manager_add_sensor(SensorManger* manager,int count);
SensorError init_all(SensorManger* manager);
SensorError calibrate_all(SensorManger* manager);
SensorError read_all(SensorManger* manager);
SensorError destroy_all(SensorManger* manager);

#endif
