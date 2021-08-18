/*************************************************************************************/
/** Implement your read sensor functions here ****************************************/
/*************************************************************************************/
#include "dht.h"
dht DHT;

int readCO2(int pin); // air quality value
int readDHT_t (int pin); // ambient temperature
int readDHT_h (int pin); // ambient humidity
int readBgt (int pin); // brightness
int readW_f (int pin); // wind force
int readW_d (int pin); // wind direction
int readWLevel (int pin); // water level in a pluviometer


/************** BASIC READING FUNCTION  Example **************************************/
unsigned char ReadSensor(int pin) {
  int output_value = analogRead(pin);
  return output_value;
}
/************** AD-HOC READING FUNCTIONS **********************************************/

int readCO2(int pin) {
  //MQ-135  Benzene, alcohol, smoke, air quality
  int mq135_adc = analogRead(pin);
  return mq135_adc;
}

int readDHT_t (int pin) {
  //DHT11 Temperatura and Humidity
    DHT.read11(pin);
    return DHT.temperature;
}

int readDHT_h (int pin) {
  //DHT11 Temperatura and Humidity
    DHT.read11(pin);
    return DHT.humidity;
}

int readBgt (int pin) {
    int output_value = analogRead(pin);
    if (output_value > 100) return 0; //shadow or darkness
    else return 1; //sun
}
int readW_f (int pin) {
  //Vane Force
    int output_value = analogRead(pin);
    output_value = 9; 
    return output_value;
}
int readW_d (int pin) {
  //Vane Direcction (degrees)
    int output_value = 35; 
    return output_value;
}
int readWLevel (int pin) {
    int output_value = analogRead(pin);
    return output_value; //level
}
