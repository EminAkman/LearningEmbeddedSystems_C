#include "sensor.h"
#include "mesafe_sens.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct {
    Sensor base;        
    float currentDistance;
} MesafeSensor;



static SensorError mesafeSens_Init(Sensor* self) 
{

    MesafeSensor* ms = (MesafeSensor*) self;
    ms->currentDistance = 2;  

    return SENSOR_OK;
}

static SensorError mesafeSens_Read(Sensor* self, float* value) 
{

    MesafeSensor* ms = (MesafeSensor*)self;
    ms->currentDistance += ((rand()%100)/100.0f) - 0.5f;
    *value = ms->currentDistance;

    if(ms->base.filter)
    {
        *value = ms->base.filter->vtable->apply(ms->base.filter, *value);
        printf("Sensor bir %s sensorudur. %s filtresinden gecirilmistir ve mesafe: %f m'dir. ID'si : %d'dir.\n",
        ms->base.name,ms->base.filter->name,ms->currentDistance, ms->base.ID);
        if(ms->base.callback == typeVerify) check_Mesafe_Sens_Callback(self);
    }

    return SENSOR_OK;
}


static SensorError mesafeSens_Calibrate(Sensor* self)
{

    return SENSOR_OK;
}

static void mesafeSens_Destroy(Sensor* self)
{
    free(self);
}

void check_Mesafe_Sens_Callback(Sensor* self)
{

    MesafeSensor* ms = (MesafeSensor*) self;
    
    for (int i = 0; i < sizeof(CallbackType) / 4; i++)
    {
        if (ms->base.callback == typeVerify && ms->currentDistance > ms->base.tresholdcallback)
        {
            printf("Uyari sensor %f esik degerini asti!!!\n", ms->base.tresholdcallback);
        }        
    }
}

static SensorVTable mesafeSens_Vtable = 
{

    .init = mesafeSens_Init,
    .read = mesafeSens_Read,
    .calibrate = mesafeSens_Calibrate,
    .destroy = mesafeSens_Destroy,
    .checkCallback = check_Mesafe_Sens_Callback,
};

Sensor* CreateMesafeSens() 
{

    MesafeSensor* Ms = malloc(sizeof(MesafeSensor));
    if (!Ms) return NULL;
    Ms->currentDistance = 0;
    Ms->base.name = "MesafeSens";
    Ms->base.vtable = &mesafeSens_Vtable;
    SensorID++;
    Ms->base.ID = SensorID;
    Ms->base.filter = createFilter(typeNoFilter);
    Ms->base.callback = typeNoCallback;
    Ms->base.tresholdcallback = 0.0;

    return (Sensor*)Ms;
}