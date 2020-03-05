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
 gloveData.writeValue("\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0");
 sensorService.addCharacteristic(gloveData);
 BLE.addService(sensorService);
 BLE.setAdvertisedService(sensorService);
 BLE.setLocalName("Salmon Glove");      
 BLE.advertise();
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

}

void loop() {
  uint8_t data[34];
  float imuData[6];
  uint16_t threadData[5];
  
  digitalWrite(LED_BUILTIN, LOW);
 BLEDevice central = BLE.central();

 if(central) {
    central.connect();
    digitalWrite(LED_BUILTIN, HIGH);
    while(central.connected()) {
     
     if(IMU.accelerationAvailable()) 
       IMU.readAcceleration(imuData[0], imuData[1], imuData[2]);
   
     if(IMU.gyroscopeAvailable()) 
       IMU.readGyroscope(imuData[3], imuData[4], imuData[5]);

     threadData[0] = analogRead(A0);
     threadData[1] = analogRead(A1);
     threadData[2] = analogRead(A2);
     threadData[3] = analogRead(A3);
     threadData[4] = analogRead(A4);

     for (int i = 0; i < 24; i++) {
      data[i] = *(((uint8_t*)imuData) + i);
     }
     for (int i = 24; i < 34; i++) {
      data[i] = *(((uint8_t*)threadData) + i - 24);
     }

     gloveData.writeValue((const void *) data, 34);
    }
 }
//}

//  Serial.println(analogRead(A0));
//  delay(100);
}
