#include "esphome.h"
// #include "Wire.h"

const uint16_t I2C_ADDRESS = 0x74;
const uint16_t POLLING_PERIOD = 5000; //milliseconds

class MyCustomSensor : public PollingComponent, public Sensor {
 public:
  // constructor
  MyCustomSensor() : PollingComponent(POLLING_PERIOD) {}
  float get_setup_priority() const override { return esphome::setup_priority::BUS; } //Access I2C bus

  void setup() override {
      //Add code here as needed
      // Wire.begin();
      // ESP_LOGD("custom","THIS IS A ESPLOGD PRINT TEST");
      // Serial.println("THIS IS A SERIAL PRINT TEST");
    }

  void update() override {
        uint8_t recvbuf[9] = {0};
        Wire.beginTransmission(I2C_ADDRESS);
        Wire.write(0xFF);
        Wire.write(0x01);
        Wire.write(0x86);
        Wire.write(0x00);
        Wire.write(0x00);
        Wire.write(0x00);
        Wire.write(0x00);
        Wire.write(0x79);
        Wire.endTransmission();
        // publish_state(42.0);
        delay(10);

        int i=0;
        Wire.requestFrom(0x74,9);
        while (Wire.available())
        {
          recvbuf[i++]=Wire.read();
        }
        // ESP_LOGD(recvbuf);
        float con = (((recvbuf[2]*256) + recvbuf[3]) * 0.1);
        publish_state(con);
    }
};
