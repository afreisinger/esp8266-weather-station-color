#include <Arduino.h>
#include <DHTesp.h>

#ifndef _SENSORWS_H
#define _SENSORWS_H


class SensorWS : public DHTesp {
    public:
        SensorWS(uint8_t pin, DHT_MODEL_t model);
        bool getValues();
    private:
        void init(); 
        uint8_t pin;
        DHT_MODEL_t model;
        ComfortState cf;
};
#endif
