#include "SensorWS.h"

SensorWS::SensorWS(uint8_t pin, DHT_MODEL_t model){
    this->pin=pin;
    this->model=model;
    init();
}

void SensorWS::init(){
    this->setup(pin, model);
    Serial.println("DHT initiated");
}

/**
 * getValues
 * Reads temperature from DHT11 sensor
 * @return bool
 *    true if temperature could be aquired
 *    false if aquisition failed
*/
bool SensorWS::getValues(){
        // Reading temperature for humidity takes about 250 milliseconds!
	    // Sensor readings may also be up to 2 seconds 'old' (it's a very slow sensor)
    TempAndHumidity newValues = this->getTempAndHumidity();
        // Check if any reads failed and exit early (to try again).
        if (this->getStatus() !=0 ){
            Serial.println("Sensor status: " + String(this->getStatusString()));
            return false;
        }
  
    float cr =this->getComfortRatio(cf, newValues.temperature, newValues.humidity);

  String comfortStatus;
  
  switch(cf) {
    case Comfort_OK:
      comfortStatus = "OK";
      break;
    case Comfort_TooHot:
      comfortStatus = "Too Hot";
      break;
    case Comfort_TooCold:
      comfortStatus = "Too Cold";
      break;
    case Comfort_TooDry:
      comfortStatus = "Too Dry";
      break;
    case Comfort_TooHumid:
      comfortStatus = "Too Humid";
      break;
    case Comfort_HotAndHumid:
      comfortStatus = "Hot and Humid";
      break;
    case Comfort_HotAndDry:
      comfortStatus = "Hot and Dry";
      break;
    case Comfort_ColdAndHumid:
      comfortStatus = "Cold and Humid";
      break;
    case Comfort_ColdAndDry:
      comfortStatus = "Cold and Dry";
      break;
    default:
      comfortStatus = "Unknown:";
      break;
  };
    Serial.print("Status\t\tTemperature(C)\t\tHumidity(%)\t\tTemperature(F)\t\tHeat(C)\t\tHeat(F)\t\tDewPoint(C)\tComfort\n");
    Serial.printf("%s\t\t%.1f\t\t\t%.0f\t\t\t%.1f\t\t\t%.1f\t\t%.1f\t\t%.1f\t\t%s\n", 
    this->getStatusString(), 
    newValues.temperature,
    newValues.humidity,
    this->toFahrenheit(newValues.temperature),
    this->computeHeatIndex(newValues.temperature, newValues.humidity, false),
    this->computeHeatIndex(this->toFahrenheit(newValues.temperature),newValues.humidity, true),
    this->computeDewPoint(newValues.temperature, newValues.humidity),
    comfortStatus.c_str());

return true;

}
