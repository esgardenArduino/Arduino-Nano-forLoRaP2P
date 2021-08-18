#include "RAK811.h"
#include "SoftwareSerial.h"


/***************************************************************************************/
/************** THIS .H CONFIGURES P2P LoRa RECEPTION **********************************/
/**************************************************************************************/

#define WORK_MODE LoRaP2P 
#define TXpin 11
#define RXpin 10 
#define DebugSerial Serial

SoftwareSerial RAKSerial(RXpin, TXpin);
RAK811 RAKLoRa(RAKSerial, DebugSerial);

int RESET_PIN = 12;
void StartLoraReceiver(void);
bool initP2P(void);
void LoRaRAK811_setup(void);
String FREQ = "868100000";  // EU free available frequency range:(860000000 - 1020000000)


/**********************************************************************************************/
/***     LORA START-UP FUNCTIONS ***************************************************************/
/**********************************************************************************************/
void LoRaRAK811_setup() {

  Serial.begin(9600);
  DebugSerial.println("STARTING. Starting LoRa transceiver...");
  StartLoraReceiver();
  DebugSerial.println("STARTED.  LoRa Transceiver Started.\n\n");
  while (!initP2P());
}

bool initP2P() {
  RAKLoRa.rk_setWorkingMode(WORK_MODE);
  DebugSerial.println("You set Working mode is OK!"); //Checking line
  if (RAKLoRa.rk_initP2P(FREQ, 7, 0, 1, 8, 14)) //if (RAKLoRa.rk_initP2P(FREQ,7,0,1,8,14))
  {
    DebugSerial.println("You init P2P parameter is OK!"); //Checking line
    return true;
  }
  return false;
}

void StartLoraReceiver() {
  pinMode(RESET_PIN, OUTPUT);
  //Setup Debug Serial on USB Port
  DebugSerial.begin(9600);
  DebugSerial.println("Serial StartUP");
  delay(600);
  digitalWrite(RESET_PIN, LOW);   // turn the pin low to Reset
  delay(600);
  digitalWrite(RESET_PIN, HIGH);    // then high to enable
  while (DebugSerial.read() >= 0) {}
  while (!DebugSerial);
  //Print debug info
  DebugSerial.println("Serial Reset");
  //Reset the RAK Module
  RAKSerial.begin(9600); // Arduino Shield
  RAKSerial.println("at+uart=9600,8,0,0,0");
  delay(400);
  digitalWrite(RESET_PIN, LOW);   // turn the pin low to Reset
  delay(400);
  digitalWrite(RESET_PIN, HIGH);    // then high to enable
  DebugSerial.println("RAK Reset Success");
  delay(100);
  DebugSerial.println(RAKLoRa.rk_getVersion());
  delay(400);
  DebugSerial.println(RAKLoRa.rk_getBand());
  delay(400);
  DebugSerial.println(RAKLoRa.rk_getP2PConfig());
}

String GetValueLora(String from) {
  String str = from + " ";
  char str_array[str.length() + 2];
  str.toCharArray(str_array, str.length());
  char* token = strtok(str_array, ",");
  int n = 5;
  while (n > 0) {
    token = strtok(0, ",");
    n--;
  }
  return token;
}
