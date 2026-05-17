#include <ArduinoBLE.h>

const char* SENSOR_CHAR_UUID = "87654321-4321-4321-4321-CBA987654321";

void setup() {
  Serial.begin(9600);

  if (!BLE.begin()) {
    while (1);
  }

  BLE.scanForName("SensorArduino");
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    BLE.stopScan();

    if (peripheral.connect()) {
      if (peripheral.discoverAttributes()) {
        BLECharacteristic ch = peripheral.characteristic(SENSOR_CHAR_UUID);

        while (peripheral.connected()) {
          int v = 0;

          ch.readValue(v);

          Serial.print(v / 100);
          Serial.print(".");

          int d = v % 100;
          if (d < 10) Serial.print("0");

          Serial.println(d);

          delay(500);
        }
      }

      peripheral.disconnect();
    }

    BLE.scanForName("SensorArduino");
  }
}