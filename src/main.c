#include "sensor.h"
#include "manager.h"
#include <stdio.h>
#include <stdlib.h>

SensorManger manager;

int main() {
    
    manager_add_sensor(&manager,2);
    printf("Toplam Sensor Sayisi : %d\n",SensorID);
    init_all(&manager);
    printf("Tum Sensorler Baslatildi\n");
    calibrate_all(&manager);

    /////////////////////////////////////////////
    /////////// TEST CODE FOR STATE  ////////////
    /////////////////////////////////////////////

    read_all(&manager);
    read_all_state(&manager);

    /*
    
    /////////////////////////////////////////////
    /////// TEST CODE FOR SENSOR CALLBACK ///////
    /////////////////////////////////////////////

    read_all(&manager);

    set_callback(&manager,0,typeVerify);
    set_callback(&manager,1,typeVerify);
    manager.sensors[0]->tresholdcallback = 25.0;
    manager.sensors[1]->tresholdcallback = 25.0;
    read_all(&manager);
    
    */

    
    
    /*
    
    /////////////////////////////////////////////
    // TEST CODE FOR FILTER AND SENSOR MANAGER //
    /////////////////////////////////////////////

    read_all(&manager);    
    manager.sensors[1]->filter = createFilter(typeMedianFilter);
    read_all(&manager);
    read_all(&manager);
    read_all(&manager);
    read_all(&manager);
    read_all(&manager);

    */ 

    destroy_all(&manager);
    
    return 0;
}
