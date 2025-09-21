#include "manager.h"
#include "enums.h"
#include "sensor.h"
#include "mesafe_sens.h"
#include "temp_sensor.h"

#include <stdio.h>
#include <stdlib.h>

float value = 0;

SensorError manager_add_sensor(SensorManger* manager,int count)
{

    for (int i = 0; i < count; i++)
    {
        if (i %2 == 1)
        {   

            Sensor* s = TempSensor_create();
            if (s == NULL)
            {
                printf("Sensor Eklenemedi\n");
                return SENSOR_ERROR;
            }
            
            manager->sensors[i]= s;
        }
        
        if (i %2 == 0)
        {
            Sensor* s = CreateMesafeSens();
            if (s == NULL)
            {
                printf("Sensor Eklenemedi\n");
                return SENSOR_ERROR;
            }
            manager->sensors[i]= s;
        }
        
    }
    printf("Sensorler Eklendi\n");
    return SENSOR_OK;
    
}

SensorError init_all(SensorManger* manager)
{

    for (int i = 0; i < SensorID; i++)
    {
        manager->sensors[i]->vtable->init(manager->sensors[i]);
    }
    return SENSOR_OK;
    
}

SensorError calibrate_all(SensorManger* manager)
{

    for (int i = 0; i < SensorID; i++)
    {
        manager->sensors[i]->vtable->calibrate(manager->sensors[i]);
    }
    printf("Tum Sensorler Kalibre Edildi\n");
    return SENSOR_OK;

}
SensorError read_all(SensorManger* manager)
{

    for (int i = 0; i < SensorID; i++)
    {
        manager->sensors[i]->vtable->read(manager->sensors[i],&value);
    }
    return SENSOR_OK;

}

SensorError destroy_all(SensorManger* manager)
{

    for (int i = 0; i < SensorID; i++)
    {
        manager->sensors[i]->vtable->destroy(manager->sensors[i]);
    }
    printf("Tum Sensorler Silindi\n");
    return SENSOR_OK;

}

SensorError set_callback(SensorManger* manager, int id, CallbackType* cb)
{

    manager->sensors[id]->callback = cb;
    return SENSOR_OK;

}