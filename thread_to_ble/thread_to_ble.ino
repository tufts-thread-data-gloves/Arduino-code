#include <Arduino.h>
#include <ArduinoBLE.h>
#include <cmath>
#include <Arduino_LSM9DS1.h>
#include <stdint.h>

const char *sensorUUID = "1b9b0000-3e7e-4c78-93b3-0f86540298f1";
const char *dataCharUUID = "1b9b0001-3e7e-4c78-93b3-0f86540298f1";

BLEService sensorService(sensorUUID);

BLECharacteristic gloveData(dataCharUUID, BLERead, 34, true);

void setup() {
//  Serial.begin(9600);
//  while(!Serial);
 while (!BLE.begin());
  while (!IMU.begin());
//  Serial.println("ok?");
 BLE.setConnectable(true);
 BLE.setAdvertisedService(sensorService);
 gloveData.writeValue("ababababababababababababababababab");
 sensorService.addCharacteristic(gloveData);
 BLE.addService(sensorService);
 BLE.setAdvertisedService(sensorService);
 BLE.setLocalName("Salmon Glove");      
 BLE.advertise();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);

}

void loop() {
  uint8_t data[34];
  float imuData[6];
  int threadData[5];
  
  digitalWrite(LED_BUILTIN, LOW);
 BLEDevice central = BLE.central();

 if(central) {
    central.connect();
    digitalWrite(LED_BUILTIN, HIGH);
    while(central.connected()) {
     
     if(IMU.accelerationAvailable()) 
       IMU.readAcceleration(imuData[0], imuData[1], imuData[2]);
   
     if(IMU.magneticFieldAvailable()) 
       IMU.readMagneticField(imuData[3], imuData[4], imuData[5]);

     threadData[0] = 0;
     threadData[1] = 0;
     threadData[2] = 0;
     threadData[3] = 0;
     threadData[4] = 0;

     for (int i = 0; i < 24; i++) {
      data[i] = *(((char*)imuData) + i);
     }
     for (int i = 24; i < 34; i++) {
      data[i] = *(((char*)threadData) + i - 24);
     }

     gloveData.writeValue((const void *) data, 34);
    }
 }
//}

//  Serial.println(analogRead(A0));
//  delay(100);
}
