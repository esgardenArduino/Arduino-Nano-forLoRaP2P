#include <Adafruit_SleepyDog.h>
#include "Lora_conf.h"
#include "send_params.h"
#include "sensor_functions.h"

/*****************************************************/
/************  LoRa HAT SET-UP ***********************/
/*****************************************************/

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; 
  }
   LoRaRAK811_setup();
   Serial.println("LoRa Set-Up.... OK.");
}

void loop() {
  
 while (1) { 

 /***************************************************************/
 /******* READ THE VALUES OF YOUR SENSORS **********************/
 /**************************************************************/
  _readSensors(); //call to the last function in this file

/**************************************************************/
/****** BUILD AN HEX STRING SERIALIZING SENSORS DATA  ********/
/*************************************************************/

  char bufLora[SizeBuffer];
  char * Data_buffer_ptr =  bufLora;

  /******* Characters 0,1 represent the garden space ************/
  strncpy (Data_buffer_ptr,  ID_NODE, 2);
  int  j = 2;


  /******* Build an HEX string with TYPE+FIELD tuples **********/
  int  i = 0;

  /******* Modify: add or remove till your sensors number ******/
  /********************* SEE send_params.h *********************/
  
  sprintf((Data_buffer_ptr + j), "%02X", TYPE0); //CO2
  j = j + 2;
  for (i = 0; i < quantityOfVal[TYPE0]; i++){
  sprintf((Data_buffer_ptr + j), "%04X", FIELD0[i]); //DATA
  j = j + 4;
  }
  
  sprintf((Data_buffer_ptr + j), "%02X", TYPE1); //Ambient temperature
  j = j + 2;
  for (i = 0; i < quantityOfVal[TYPE1]; i++){
  sprintf((Data_buffer_ptr + j), "%04X", FIELD1[i]); //DATA
  j = j + 4;
  }
  
  sprintf((Data_buffer_ptr + j), "%02X", TYPE2); //Ambient humidity
  j = j + 2;
  for (i = 0; i < quantityOfVal[TYPE2]; i++){
  sprintf((Data_buffer_ptr + j), "%04X", FIELD2[i]); //DATA
  j = j + 4;
  }
  
  sprintf((Data_buffer_ptr + j), "%02X", TYPE3); //Brightness
  j = j + 2;
  for (i = 0; i < quantityOfVal[TYPE3]; i++){
  sprintf((Data_buffer_ptr + j), "%04X", FIELD3[i]); //DATA
  j = j + 4;
  }
  
 /* sprintf((Data_buffer_ptr + j), "%02X", TYPE4); //Wind
  j = j + 2;
  for (i = 0; i < quantityOfVal[TYPE4]; i++){
  sprintf((Data_buffer_ptr + j), "%04X", FIELD4[i]); //DATA
  j = j + 4;
  }*/
  
  Serial.println(" Buffer filled .....  ");
  Serial.print(bufLora);
  Serial.println(" ");
  
  char* stringLora = "0";
  byte ix = SizeBuffer;
  while ( ix-- ) *( stringLora + ix ) = *( bufLora + ix ); // dest and src are your 2 array names


  /******************************************************************************************/
  /** Send the HEX string by LoRa to Arduino UNO WiFi ***************************************/
  /** Send the packet 3 times and sleeps for a while ****************************************/
  /******************************************************************************************/

  int index = 0;
  for (index = 0; index < 2; index++) {//send the same message twice as a fault mechanism
  if (RAKLoRa.rk_sendP2PData(0, "34", stringLora))
  {
      String ver = RAKLoRa.rk_recvData();
      if (ver == STATUS_P2PTX_COMPLETE)
      {
        DebugSerial.println("Buffer sent.");
      } else {
        DebugSerial.print(ver); //Checking line
      }
  }
  delay (1000);
  }
  
  
  /******************************************************************************************/
  /** Wait for a time before reading again **************************************************/
  /******************************************************************************************/
   DebugSerial.println("Sleeping ...."); //Checking line
   delay (100);
   unsigned long int sleepMS = 0;
   while (sleepMS < 300000){ //60000 1m or 300000 for 5m
   sleepMS = sleepMS + Watchdog.sleep(1000);//1 seconds
    }
   DebugSerial.println("Awake again! ..."); //Checking line
   
 }

}
/********************************************************************************************/
/** Modify this function depending on your sensors ******************************************/
/** DATA is assume as integer ***************************************************************/
/********************************************************************************************/
/* The function load read values to FIELD [i] variables*/

void _readSensors() {
      
      FIELD0[0] = readCO2(A0); // Modify the analog/digital pin number
      DebugSerial.println("  FIELD0 =  ");
      DebugSerial.println(FIELD0[0]);
            delay(100);
      FIELD1[0] = readDHT_t(A1); // Modify the analog/digital pin number
      DebugSerial.println("  FIELD1 =  ");
      DebugSerial.println(FIELD1[0]);
            delay(100);
      FIELD2[0] = readDHT_h(A1); // Modify the analog/digital pin number
      DebugSerial.println("  FIELD2 =  ");
      DebugSerial.println(FIELD2[0]);     
            delay(100);
      FIELD3[0] = readWLevel (A2); // Modify the analog/digital pin number
      DebugSerial.println("  FIELD3 =  ");
      DebugSerial.println(FIELD3[0]);      
            delay(100);
    
    /*  Add, change or modify according with your sensors  */        

 }
