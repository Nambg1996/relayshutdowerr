#include <ArduinoJson.h>
#include "handerFiles.h"
#include "myBLE.h"
#include "interactBeacon.h"
#include "masterTransfer.h"
#include "serviceMaster.h"
#include <string>
#include "registermanual.h"



void setup()
{
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(LED_BEACON, OUTPUT);
  digitalWrite(LED_BEACON, LOW);
  beginMyble();
  SPIFFS.format();
  SPIFFS.begin();
  createDataJsonFile();
  processDataStore(dataStore);



  masterBegin();
}

void transmitResultFromScan() {
  // Your function logic goes here
    const char *allScanResultRssiAdress = allAdressRssi(rssi_and_address);
    const char *pickup5ResultFromScan = serviceAdressValue(allScanResultRssiAdress);
     masterTransmit(prefixs.allInforScan+String(pickup5ResultFromScan));
}

void transmitResultRssi_adress_registered() {
  // Your function logic goes here

     masterTransmit(prefixs.addressValueRegister+addressAndValueRegister());
}

void transmitResultfrompickupBeaconAdressRegister() {
  // Your function logic goes here
      String dataRegister = getDataJson();
     String dataRegister5 = pickupBeaconAdress(dataRegister, 5);
     masterTransmit(prefixs.addressRegister+dataRegister5);
}



//unsigned long track_time_start = millis();
int numberrun=0;
void loop()
{
 
  
  interractBeaconWithButton();
  
  getParameterBLE(toTurnOnLed);

  getParameterBLE(getRssiAndAdressOfBeaconRegisted);

  BLEDevice::getScan()->start(scanTime);
  String dataRegister = getDataJson();

  
  Serial.println(dataRegister);

}


