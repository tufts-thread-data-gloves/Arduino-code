#include <Arduino.h>
#include <ArduinoBLE.h>
#include <cmath>
#include <Arduino_LSM9DS1.h>

const char *sensorUUID = "1b9b0000-3e7e-4c78-93b3-0f86540298f1";
const char *accCharUUID = "1b9b0001-3e7e-4c78-93b3-0f86540298f1";
const char *gyrCharUUID = "1b9b0002-3e7e-4c78-93b3-0f86540298f1";
//const char *sensorAXUUID = "1b9b0001-3e7e-4c78-93b3-0f86540298f1";
//const char *sensorAYUUID = "1b9b0002-3e7e-4c78-93b3-0f86540298f1";
//const char *sensorAZUUID = "1b9b0003-3e7e-4c78-93b3-0f86540298f1";
//const char *sensorGXUUID = "1b9b0004-3e7e-4c78-93b3-0f86540298f1";
//const char *sensorGYUUID = "1b9b0005-3e7e-4c78-93b3-0f86540298f1";
//const char *sensorGZUUID = "1b9b0006-3e7e-4c78-93b3-0f86540298f1";

BLEService sensorService(sensorUUID);
//BLEFloatCharacteristic accelX(sensorAXUUID, BLERead);
//BLEFloatCharacteristic accelY(sensorAYUUID, BLERead);
//BLEFloatCharacteristic accelZ(sensorAZUUID, BLERead);
//BLEFloatCharacteristic gyroX(sensorGXUUID, BLERead);
//BLEFloatCharacteristic gyroY(sensorGYUUID, BLERead);
//BLEFloatCharacteristic gyroZ(sensorGZUUID, BLERead);
//BLEFloatCharacteristic sensorArr[6] = {accelX, accelY, accelZ, gyroX, gyroY, gyroZ};
//BLELongCharacteristic accChar(accCharUUID, BLERead);
//BLELongCharacteristic gyrChar(gyrCharUUID, BLERead);
BLEShortCharacteristic threadChar(accCharUUID, BLERead);
BLEShortCharacteristic thread2Char(gyrCharUUID, BLERead);


void setup() {
  while (!BLE.begin());
  while (!IMU.begin());
  
  BLE.setConnectable(true);
  BLE.setAdvertisedService(sensorService);
//  sensorService.addCharacteristic(accelX);
//  sensorService.addCharacteristic(accelY);
//  sensorService.addCharacteristic(accelZ);
//  sensorService.addCharacteristic(gyroX);
//  sensorService.addCharacteristic(gyroY);
//  sensorService.addCharacteristic(gyroZ);
//  accelX.writeValue(0);
//  gyrChar.writeValue(0);
//  accChar.writeValue(0);
//  accelZ.writeValue(0);
//  gyroX.writeValue(0);
//  gyroY.writeValue(0);
//  gyroZ.writeValue(0);
//  sensorService.addCharacteristic(accChar);
//  sensorService.addCharacteristic(gyrChar);
//  sensorService.addCharacteristic(accelY);
  thread2Char.writeValue(0);
  threadChar.writeValue(0);
  sensorService.addCharacteristic(thread2Char);
  sensorService.addCharacteristic(threadChar);
  BLE.addService(sensorService);
  BLE.setAdvertisedService(sensorService);
  BLE.setLocalName("Salmon Glove");      
  BLE.advertise();
//  Serial.begin(9600);
//  while(!Serial);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
//  Serial.println("exit setup");
//  Serial.println(BLE.address());
//  Serial.println(imuChar.value());
}

void loop() {
  digitalWrite(LED_BUILTIN, LOW);
  BLEDevice central = BLE.central();

  if(central) {
    central.connect();
//    Serial.println("connected to something\n");
    digitalWrite(LED_BUILTIN, HIGH);
//    delay(200);
    while(central.connected()) {
//      Serial.println("we are still connected");
      delay(100);
//      float xyz[6];
//      
//      if(IMU.accelerationAvailable()) {
//        IMU.readAcceleration(xyz[0], xyz[1], xyz[2]);
//        for (int i = 0; i < 3; i++) {
//          if (abs(xyz[i] - sensorArr[i]) > 0.1) sensorArr[i].writeValue(xyz[i]);
//        }
//      }
//    
//      if(IMU.gyroscopeAvailable()) {
//        IMU.readGyroscope(xyz[3], xyz[4], xyz[5]);
//        for (int i = 0; i < 3; i++) {
//          if (abs(xyz[i] - sensorArr[i + 3]) > 0.1) sensorArr[i + 3].writeValue(xyz[i]);
//        }
//      }
//      int agh[6] = {(int)(127*xyz[0]/4), (int)(127*xyz[1]/4), (int)(127*xyz[2]/4),
//                    (int)(127*xyz[3]/2000), (int)(127*xyz[4]/2000), (int)(127*xyz[5]/2000)};
//
//      char accint[4] = {(char)agh[0],
//                          (char)agh[1],
//                          (char)agh[2],
//                          0};
//      char gyrint[4] = {(char)agh[3],
//                          (char)agh[4],
//                          (char)agh[5],
//                          0};
//      Serial.println(agh[0]);
//      Serial.println(accint[0]);
//      Serial.println((xyz[0]/4)*127);
//      Serial.println((char)((int)(xyz[0]/4)*127)));
//      Serial.println((char)(int)((xyz[0]/4)*127));
//      Serial.println(*(long*)gyrint);
//      accChar.writeValue(*((long*)accint));
//      gyrChar.writeValue(*((long*)gyrint));
//      Serial.println(*((long*)fakelong));
//      imuChar.writeValue((byte*)xyz, 24);
//      char val[24];
//      imuChar.readValue(val, 24);
//      Serial.println(val);
      threadChar.writeValue((short)analogRead(A0));
      thread2Char.writeValue((short)analogRead(A1));
    }
  }

//  Serial.println(analogRead(A0));
//  delay(100);
}
