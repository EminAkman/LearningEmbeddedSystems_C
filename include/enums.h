#ifndef ENUMS_H
#define ENUMS_H

// Filter types
typedef enum 
{

    typeNoFilter = 0,
    typeMedianFilter = 1,

} FilterType;

// Sensor error codes
typedef enum 
{
    SENSOR_OK = 0,
    SENSOR_ERROR = 1,
} SensorError;

#endif