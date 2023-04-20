// Wire Master Writer
// ESP32 I2C slave library: <https://github.com/gutierrezps/ESP32_I2C_Slave>
#include <Arduino.h>
#include <Wire.h>
#include <WirePacker.h>

#define SDA_PIN 21
#define SCL_PIN 25
#define I2C_SLAVE_ADDR 0x04

void masterBegin()
{      
      // start serial for output
    Wire.begin(SDA_PIN, SCL_PIN);   // join i2c bus
}

void masterTransmit(String dataTransfer)
{
   // static unsigned long lastWireTransmit = 0;
    static byte x = 0;
    // send data to WireSlave device every 1000 ms
    //if (millis() - lastWireTransmit > 1000) {
        // first create a WirePacker that will assemble a packet
        WirePacker packer;
        // then add data the same way as you would with Wire
        const char *data = dataTransfer.c_str();
        packer.write(data);
        packer.write((char) 0);
        // after adding all data you want to send, close the packet
        packer.end();
        // now transmit the packed data
        Wire.beginTransmission(I2C_SLAVE_ADDR);
        while (packer.available()) { 
               // write every packet byte
            Wire.write(packer.read());
        } 
        Wire.endTransmission();         // stop transmitting
        //lastWireTransmit = millis();
   // }
}